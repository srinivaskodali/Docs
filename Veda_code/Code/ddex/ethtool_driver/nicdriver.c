
/*A RealTek RTL-8139 Fast Ethernet driver for Linux.*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/compiler.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/irq.h>

static int nic_init(void);
static void nic_cleanup(void);

#define RX_BUF_LEN  8912
#define TX_BUF_LEN 1600 
static struct pci_device_id nic_idtable[] = {
	{0x10ec, 0x8139, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{0,}
};

enum nic_registers {
	TxStatus0 = 0x10,       /* Transmit status (Four 32bit registers). */
	TxAddr0 = 0x20,         /* Tx descriptors (also four 32bit). */
	RxBuf = 0x30,
	ChipCmd = 0x37,
	RxBufPtr = 0x38,
	IMR = 0x3C,
	ISR = 0x3E,
	Config3 = 0x59,
	Config5 = 0xD8,         
};
enum ChipCmdBits {
	CmdReset = 0x10,
	CmdRxEnb = 0x08,
	CmdTxEnb = 0x04,
	RxBufEmpty = 0x01,
};

enum Config3Bits {
	Cfg3_LinkUp    = (1 << 4), /* 1 = wake up on link up */
	Cfg3_Magic     = (1 << 5), /* 1 = wake up on Magic Packet (tm) */
};

enum IntrStatusBits {
	RxFIFOOver = 0x40,
	RxOverflow = 0x10,
	TxErr = 0x08,
	TxOK = 0x04,
	RxErr = 0x02,
	RxOK = 0x01,
	TxStatOK = 0x8000,
	RxAckBits = RxFIFOOver | RxOverflow | RxOK,
};



struct nic_private{
	struct pci_dev *pdev;
	void __iomem *iobase;
	int regs_len;
	int irq;
	int rxcount;
	int rxdroped;
	int txcount;
	int txdroped;
	unsigned int cur_rx;
	dma_addr_t txbuf_dma; 
	dma_addr_t rxring_dma;
	void *rxbuf;
	void *txbuf;

};


/*Report driver information*/
static void nic_get_drvinfo(struct net_device *dev,struct ethtool_drvinfo *info)
{
	struct nic_private *np = netdev_priv(dev);
	strcpy(info->driver,"NIC DRIVER");
	strcpy(info->version, "1.0");
	strcpy(info->bus_info, pci_name(np->pdev));
	info->regdump_len = np->regs_len;
}

/*Get length of the registers */
static int nic_get_regs_len(struct net_device *dev)
{
	        struct nic_private *np = netdev_priv(dev);
		        return np->regs_len;
}

/*Get device registers*/
static void nic_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *regbuf)
{
	struct nic_private *np = netdev_priv(dev);

	memcpy_fromio(regbuf, np->iobase, regs->len);
}

/*Report whether Wake-on-Lan is enabled*/
static void nic_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{

	struct nic_private *np = netdev_priv(dev);

	u8 cfg3 = readb(np->iobase+Config3); /*read config reg 3*/

	wol->supported = WAKE_PHY | WAKE_MAGIC
		| WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;

	wol->wolopts = 0;

	if (cfg3 & Cfg3_LinkUp)
		wol->wolopts |= WAKE_PHY;

	if (cfg3 & Cfg3_Magic)
		wol->wolopts |= WAKE_MAGIC;

}	

/*Report ring sizes */
static void  nic_get_ringparam(struct net_device *dev, struct ethtool_ringparam  *ering){
	ering->rx_max_pending = RX_BUF_LEN - 1;
	ering->rx_mini_max_pending = 0;

}


/* Set the ethtool Wake-on-LAN settings. */

static int nic_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct nic_private *np = netdev_priv(dev);
	u8 cfg3;

	cfg3 = readb(np->iobase+Config3); /*read config reg3*/

	if (wol->wolopts & WAKE_PHY)
		cfg3 |= Cfg3_LinkUp;
	if (wol->wolopts & WAKE_MAGIC)
		cfg3 |= Cfg3_Magic;

	writeb(cfg3,np->iobase+Config3);

	return 0;
}

/*Get link status*/
static u32 nic_get_link(struct net_device *dev)
{
	return netif_carrier_ok(dev) ? 1 : 0;	
}


static struct ethtool_ops nic_ethtool_ops = {
	.get_drvinfo            = nic_get_drvinfo,
	.get_regs_len           = nic_get_regs_len,
	.get_regs               = nic_get_regs,
	.get_wol                = nic_get_wol,
	.set_wol                = nic_set_wol,
	.get_ringparam  	= nic_get_ringparam,
	.get_link               = nic_get_link,
	

};
                

static int nic_poll(struct net_device *dev, int *budget)
{

	struct nic_private *np = netdev_priv(dev);

	int received = 0;
	unsigned char *where = np->rxbuf;
	unsigned int cur_rx = np->cur_rx;
	printk("\nIn Poll...");

	while(netif_running(dev)&&(readb(np->iobase+ChipCmd)&RxBufEmpty) == 0){

		u32 offset = cur_rx % RX_BUF_LEN;
		u32 rx_status;
		u32 rx_size;
		unsigned int pkt_size;
		struct sk_buff *skb;

		 /* read size+status of next frame from DMA ring buffer */
		rx_status = *(u32 *) (where + offset);
		rx_size = rx_status >> 16;
		pkt_size = rx_size - 4;


		/*allocate skbuf  */
		skb = dev_alloc_skb (pkt_size + 2);
		if(skb){

			skb->dev = dev;
			skb_reserve (skb, 2);   /* 16 byte align the IP fields. */
			memcpy(skb->data, where + offset+4,pkt_size);

			skb_put (skb, pkt_size);
			skb->protocol = eth_type_trans (skb, dev);

			netif_receive_skb (skb);
		} else {

			printk (KERN_WARNING" dropping packet.%s\n",dev->name);
			np->rxdroped++;
			goto out;
		}
		
		received++;
		np->rxcount++;

		cur_rx = (cur_rx + rx_size + 4 + 3) & ~3;
		writel(cur_rx,np->iobase+RxBufPtr);

		np->cur_rx = cur_rx;
	}

out:
	return received;

																                                           
}

/*put the fram into trasmition buffer*/
static int nic_start_xmit (struct sk_buff *skb, struct net_device *dev)
{

	/*get our private struct */
	struct nic_private *np = netdev_priv(dev);
	void __iomem *ioaddr = np->iobase;
	
	unsigned int len = skb->len;

	printk("In start_xmit");
	
	/*see if frame size is more than our trasmition buffer*/
	if (likely(len < TX_BUF_LEN)) {		
		if (len < ETH_ZLEN)  
			memset(np->txbuf, 0, ETH_ZLEN);
		skb_copy_and_csum_dev(skb, np->txbuf);
		dev_kfree_skb(skb);
	} else {
		dev_kfree_skb(skb);
		np->txdroped++;
		return 0;
	}

	/*tell  device size of frame and threasold  */
        writel(max(len, (unsigned int)ETH_ZLEN),ioaddr+TxStatus0 );

	return 0;

}											                                  
static irqreturn_t nic_interrupt(int irq, void *dev_num,struct pt_regs *regs)
{
	struct net_device *dev = (struct net_device *)dev_num;
	struct nic_private *np = netdev_priv(dev);
	u16 status;
	int txstatus;
	u16 handled=0;

	printk("In interrupt...");

	status = readb(np->iobase+ISR);

	 /* shared irq? */
	if (status == 0)
		goto out;

	handled = 1;
	
	/* Receive packets are processed by poll routine.
	   If not running start it now. */
	if(status & RxAckBits){
		if (netif_rx_schedule_prep(dev))
			__netif_rx_schedule(dev);
	}

	/*handle trasmission interrupts*/
	 if (status & (TxOK | TxErr)) {
		 /*get txstatus form TSD*/
		 txstatus= readl(np->iobase+TxStatus0);
		 if (!(txstatus & TxStatOK))
			 goto out;  /* It still hasn't been Txed */

			 np->txcount++;
		 if (status & TxErr)
			 writew (TxErr,np->iobase+ISR);
	 }


out:
	return IRQ_RETVAL(handled);
}


static void init_registers(struct net_device *dev)
{
	struct nic_private *np = netdev_priv(dev);
	/* Fill TSAD with our Transmission buf add */
      	writel (np->txbuf_dma, np->iobase + TxAddr0);

	/*fill RBStart register with ring buf addr*/
	writel(np->rxring_dma,np->iobase+RxBuf);

	/*enable the reception and transmission*/
	writeb(CmdRxEnb|CmdTxEnb,np->iobase+ChipCmd);

	/*Clear interrupt status register*/
	writeb(0xff,np->iobase+ISR);
	/* Enable interrupts*/
	writeb(0x73,np->iobase+IMR);
}

static void nic_reset_chip(struct net_device *dev)
{
	struct nic_private *np = netdev_priv(dev);

	/*reset the chip*/
	writeb(CmdReset, np->iobase + ChipCmd);
	
	/*wait till reset is over*/
	while(readb(np->iobase + ChipCmd ) & CmdReset);
}




static int nic_open(struct net_device *dev)
{
	struct nic_private *np = netdev_priv(dev);
	int rc;
	printk("In Open...");

	/* register isr */
	rc=request_irq(np->irq,nic_interrupt,IRQF_SHARED,dev->name,(void*)dev);
	if (rc)
		return rc;	

	/*allocate ring buffer for received packets*/
        np->rxbuf = pci_alloc_consistent(np->pdev,RX_BUF_LEN,&np->rxring_dma);
	if (!np->rxbuf) {
		printk(KERN_ERR "Could not allocate DMA memory.\n");
		return -ENOMEM;
	}

	/*allocate memory for trasmission packets*/
	np->txbuf = pci_alloc_consistent(np->pdev,TX_BUF_LEN,&np->txbuf_dma);
	if(!np->txbuf){
		printk(KERN_ERR "Could not allocate DMA memory.\n");
		return -ENOMEM;
	}

	np->txcount=0;
	np->rxcount=0;
	np->rxdroped=0;
	np->txdroped=0;

	nic_reset_chip(dev);
	init_registers(dev);


	netif_start_queue(dev);
	return 0;

}


static int nic_close (struct net_device *dev)
{
	struct nic_private *np = netdev_priv(dev);
	netif_stop_queue (dev);
      /* Stop the chip's Tx and Rx DMA processes. */
	pci_free_consistent(np->pdev, RX_BUF_LEN,np->rxbuf, np->rxring_dma);
	pci_free_consistent(np->pdev, TX_BUF_LEN,np->txbuf, np->txbuf_dma);
	np->rxbuf = NULL;
	np->txbuf = NULL;
	free_irq (dev->irq, dev);
	return 0;
}

	                            


static int  nic_probe(struct pci_dev *pdev,const struct pci_device_id *ids)
{
	struct net_device *dev;
	struct nic_private *np;
	int  rc;
	void __iomem *memio;
	int err;
	unsigned long mmio_start, mmio_len;

	/*Enable the device */
	rc = pci_enable_device(pdev);
	if (rc)
		goto err_out;

	/*Get base address IO*/
	mmio_start = pci_resource_start(pdev, 1);
	mmio_len = pci_resource_len(pdev,1);

	rc = pci_request_regions (pdev, "nic driver");
	if (rc)
		goto err_out;

	/*set pci busmastering*/
	pci_set_master(pdev);

	/* ioremap MMIO region */
	memio = pci_iomap(pdev, 1, 0);
	if (memio == NULL) {
		dev_err(&pdev->dev, "cannot remap MMIO, aborting\n");
		rc = -EIO;
		goto err_out;
	}


	/*allocate net_device  object*/
	dev = alloc_etherdev(sizeof(struct nic_private));
	if (!dev) {
		rc = -ENOMEM;
		printk(KERN_ERR "alloc_etherdev failed\n");
		goto err_out;
	}

	dev->base_addr = (long) memio;
	np=netdev_priv(dev);
	np->pdev = pdev;
	np->iobase=memio;
	np->regs_len=mmio_len;
	np->irq=pdev->irq;


	dev->open = nic_open;
	dev->stop = nic_close;
	dev->hard_start_xmit = nic_start_xmit;// address of transmission fuction
	dev->poll = nic_poll;// address of reception 
	dev->ethtool_ops = &nic_ethtool_ops;// ioctl's
	dev->irq = pdev->irq;

	/*regiset net device with network layer*/
	err = register_netdev(dev);
	if (err) {
		printk("Cannot register net device, aborting.\n");
		goto err_out;		
	}	
	pci_set_drvdata(pdev, dev);

	return 0;

err_out:
	return rc;

}

static void  nic_remove(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata (pdev);
	struct nic_private *np = netdev_priv(dev);
	if (dev != NULL){
	unregister_netdev (dev);

	if (np->iobase)
		pci_release_regions (pdev);
	free_netdev(dev);
	pci_set_drvdata (pdev, NULL);						                                        
	pci_disable_device (pdev);
	}
}


static struct pci_driver nic_driver = {
	.name           = "nicdriver",
	.id_table       = nic_idtable, //device ids
	.probe          = nic_probe,// init routine of driver
	.remove         = nic_remove,// clean up routine of driver 
};

/*Module initilization routine*/
static int __init nic_init(void)
{
	printk("\nRegistering nicdriver...");
	return pci_register_driver(&nic_driver);
}
/*module cleanup routine*/
static void __exit nic_cleanup(void)
{
	        pci_unregister_driver(&nic_driver);
}

module_init(nic_init);
module_exit(nic_cleanup);
MODULE_LICENSE("GPL");
