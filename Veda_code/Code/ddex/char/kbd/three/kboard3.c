/* Testing a Keyboard device driver
 * ** Team: Veda
 * ** Version: 1.0
 *    Kversion: 2.6
 *
 *    Changes after 2.6.29 Version:
 *    1.device_create()
 *    2.device_destroy()
 *    */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <asm/processor.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/serio.h>
#include <linux/wait.h>
#include <linux/irq.h>
#include <linux/version.h>
#include <asm/io.h>
#include "kboard.h"

#define KB_INT 1


MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Keyboard Device Driver - Test");
MODULE_LICENSE("GPL");

static int init_kb(void);
static void exit_kb(void);

module_init(init_kb);
module_exit(exit_kb);

/* Forward declaration of functions */
static int kb_open(struct inode *inode,
			    struct file  *file);
static int kb_release(struct inode *inode,
		            struct file *file);
static int kb_read(struct file *file, 
		            char *buf,
			    size_t lbuf,
			    loff_t *ppos);

static irqreturn_t kb_interrupt(int,void *);

/* Define the mapping structure */
static struct file_operations kb_file_ops;

static int kb_id;
static struct cdev *veda_cdev;
dev_t mydev;
static unsigned char some_data=100;

static wait_queue_head_t mykb_queue;
int wtevnt;
static unsigned int upcode;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
static struct class_simple *veda_class=NULL;//udev support
#else
static struct class *veda_class=NULL;//udev support
#endif

static int init_kb(void)
{
	unsigned int ret;
	kb_file_ops.owner = THIS_MODULE,
	kb_file_ops.read = kb_read;
	kb_file_ops.open = kb_open;
	kb_file_ops.release = kb_release;
     	/*kb_drv.driver.name = "mykb";
	kb_drv.interrupt   =  kb_interrupt;
	kb_drv.connect	   =  kb_connect; 	 */
	
        ret=alloc_chrdev_region(&mydev,0,1,"mykb");

        kb_id= MAJOR(mydev);//extract major no

        /* Let's Start Udev stuff */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
        veda_class = class_simple_create(THIS_MODULE,"Veda");
        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }

        class_simple_device_add(veda_class,mydev,NULL,"mykb");
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,14)
        veda_class = class_create(THIS_MODULE,"Veda");
        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }

        device_create(veda_class,NULL,mydev,NULL,"mykb");
#endif

        /*Register our character Device*/
        veda_cdev= cdev_alloc();


        veda_cdev->owner=THIS_MODULE;
        veda_cdev->ops= &kb_file_ops;

        ret=cdev_add(veda_cdev,mydev,1);
        if( ret < 0 ) {
                printk("Error registering device driver\n");
                return ret;
        }
        printk("Device Registered with MAJOR NO[%d]\n",kb_id);
	
      if(request_irq(KB_INT,kb_interrupt,IRQF_SHARED, "mykb",(void *)&some_data)){
                printk(KERN_ERR "mykb: cannot register IRQ %d\n", 8);
                return -EIO;
        }
	init_waitqueue_head( &mykb_queue );

        printk("mykb interrupt registered\n");

	return 0;
}

static void exit_kb(void)
{
	free_irq(KB_INT,&some_data);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
        class_simple_device_remove(mydev);
        class_simple_destroy(veda_class);
#else
        device_destroy(veda_class,mydev);
        class_destroy(veda_class);
#endif

unregister_chrdev_region(mydev,1);
        cdev_del(veda_cdev);
	printk("\n Module removed");
}

#define SUCCESS 0

static int kb_open(struct inode *inode,
			    struct file  *file)
{
	static int counter = 0;
	counter++;
	printk("Number of times open() was called: %d\n", counter);
	printk("Process id of the current process: %d\n", current->pid );
	return SUCCESS;
}

static int kb_release(struct inode *inode,
		            struct file *file)
{
	return SUCCESS;
}

static int kb_read(struct file *file, 
		            char *buf,
			    size_t lbuf,
			    loff_t *ppos)
{
	int ret;
	wtevnt=0;
	wait_event_interruptible(mykb_queue,wtevnt==1);
        //interrupt handler will be waking up us.
        ret=copy_to_user(buf,&upcode,1);
        return 1;

	
}

static irqreturn_t kb_interrupt(int irq, void *dev_id)
{
	unsigned char scancode;
	scancode = read_kbd_input();
        printk("scancode = %d\n",scancode);
	upcode=scancode;
	wtevnt=1;
	wake_up_interruptible(&mykb_queue);
	return 0;
}
