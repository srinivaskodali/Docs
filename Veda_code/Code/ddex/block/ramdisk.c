/*
 * A sample,simple block driver.
 ** Team: Veda
 ** Version: 1.0
 *  Kversion: 2.6
 *
 * Changes after 2.6.29 Version:
 *  1.device_create()
 *  2.device_destroy()
 *  3.Parameters of sbd_open() are changed.
 *  4.Used rq_for_each_segment instead of __rq_for_each_bio() and bio_for_each_segment().
 *  5.end_that_request_first(),end_that_request_last() and blkdev_dequeue_request() are
 *    replaced by __blk_end_request().
 *   
 **/

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/hdreg.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/blkpg.h>
#include <linux/version.h>
static int major_num = 0;
module_param(major_num, int, 0);
static int hardsect_size = 512;
module_param(hardsect_size, int, 0);
static int nsectors = 16024;	/* How big the drive is */
module_param(nsectors, int, 0);
static struct class *veda_class = NULL;

/*device private structure*/
static struct sbd_device {
	unsigned long size;	//size of the device
	spinlock_t lock;
	u8 *data;		//array to store disk data
	struct gendisk *gd;	//kernel representation of device
} Device;
dev_t mydev;

#define KERNEL_SECTOR_SIZE 512
static void sbd_request(struct request_queue *q);


/* Our request queue. */
static struct request_queue *Queue;
static int sbd_open(struct block_device *bd, fmode_t pos)
{
	return 0;
}

/* The device operations structure.*/
static struct block_device_operations sbd_ops = {.owner =
	    THIS_MODULE,.open = sbd_open,
};



/*do_actual_req : Performs actuall request process */ 
void do_actual_req(struct request *req)
{
	int max_sectors,dir, size;
	char *addr;
        int error;
         struct req_iterator iter;
	struct bio_vec *bv;	/*points to each segment in the bio */
	char *buffer;		/*temp buf */
	int sector = req->sector;	/*starting sector */
	max_sectors = req->nr_sectors;	/*total number of sectors to process */

	/*this should not cross our device limit */
	if (sector > nsectors || (sector + max_sectors) > nsectors) {
		end_request(req, 0);
		return;
	}

	/*request direction */
	dir = rq_data_dir(req);

	/*
	 *Calculate  address  where we need to read/write
	 *(i.e starting address of devcie + sector*sizeof(sector))
	 */
	addr = Device.data + (sector << 9);
	rq_for_each_segment(bv, req, iter) {	/*get each bio from request */
			size = bv->bv_len;	//size of current segment
			buffer = page_address(bv->bv_page) + bv->bv_offset;
			if (dir == WRITE){
			   printk("WRITING TO DISK\n");
			   memcpy(addr, buffer, size);
			}else {
			  printk("READING FROM DISK\n");
			  memcpy(buffer, addr, size);
			}
			addr += size;
		
        }
         error = req->errors ? -EIO:0;
        __blk_end_request(req, error,req->nr_sectors<<9);
}
static void sbd_request(struct request_queue *q)
{
	struct request *req;

	/*take requests one by one from the request queue and process it */
	while ((req = elv_next_request(q)) != NULL) {
		if (!blk_fs_request(req)) {	//check if it is read/write request
			end_request(req, 0);	//if not end this request
			continue;
		}

		/*process the request */
		do_actual_req(req);
	}
}
static int __init sbd_init(void)
{

	/* Set up our device information. */
	Device.size = nsectors * hardsect_size;
	spin_lock_init(&Device.lock);
	Device.data = vmalloc(Device.size);
	if (Device.data == NULL)
		return -ENOMEM;
	memset(Device.data, 0, Device.size);

	/* Get a request queue. */
	Queue = blk_init_queue(sbd_request, &Device.lock);
	if (Queue == NULL)
		goto out;
	blk_queue_hardsect_size(Queue, hardsect_size);

	/* Get registered. */
	major_num = register_blkdev(major_num, "sbd");
	if (major_num <= 0) {
		printk(KERN_WARNING "sbd: unable to get major number\n");
		goto out;
	}
	mydev = MKDEV(major_num, 0);
	veda_class = class_create(THIS_MODULE, "Veda22");
	if (IS_ERR(veda_class)) {
		printk(KERN_ERR "Error registering veda class\n");
	}
	device_create(veda_class, NULL, mydev, NULL, "sbd0");
	Device.gd = alloc_disk(1);
	if (!Device.gd)
		goto out_unregister;
	Device.gd->major = major_num;
	Device.gd->first_minor = 0;
	Device.gd->fops = &sbd_ops;
	Device.gd->private_data = &Device;
	strcpy(Device.gd->disk_name, "sbd0");
	set_capacity(Device.gd,nsectors * (hardsect_size / KERNEL_SECTOR_SIZE));
	Device.gd->queue = Queue;
	add_disk(Device.gd);
	return 0;

out_unregister:unregister_blkdev(major_num, "sbd");
out:vfree(Device.data);
	return -ENOMEM;
}
static void __exit sbd_exit(void)
{
	del_gendisk(Device.gd);
	put_disk(Device.gd);
	device_destroy(veda_class, mydev);
	class_destroy(veda_class);
	unregister_blkdev(major_num, "sbd");
	blk_cleanup_queue(Queue);
	vfree(Device.data);
	printk("\n Module Removed\n");
} 
module_init(sbd_init);
module_exit(sbd_exit);
MODULE_LICENSE("Dual BSD/GPL");
