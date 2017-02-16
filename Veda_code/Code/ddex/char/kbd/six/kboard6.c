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

/**
 * Instead of having init_module and cleanup_module
 * we will use the macros module_init and module_exit
 * to set the init and cleanup functions
 **/

static int init_char_device(void);
static void exit_char_device(void);

module_init(init_char_device);
module_exit(exit_char_device);

/**
 * Since this is a character device driver we need to provide
 * support for having read and write operations on this device.
 *
 * Once we do that the user will be able to use the standard
 * functions like fopen(), fclose() or open() and close() functons
 * provided in stdio.h or stdlib.h to read and write the device.
 *
 * So we will create a structure called char_device_file_ops
 * that maps functiality on to the function names in this driver
 * */

/* Forward declaration of functions */
static int char_device_open(struct inode *inode,
			    struct file  *file);
static int char_device_release(struct inode *inode,
		            struct file *file);
static int char_device_read(struct file *file, 
		            char *buf,
			    size_t lbuf,
			    loff_t *ppos);

static irqreturn_t kb_interrupt(int,void *);

/*static irqreturn_t kb_interrupt(struct serio *,unsigned char,unsigned int,
				struct pt_regs *);
static void kb_connect(struct serio *,struct serio_driver *);*/

/* Define the mapping structure */
static struct file_operations char_device_file_ops;

/**
 * The initialization routine.
 *
 * This function should register with Linux Kernel that this module
 * is a character device driver. 
 * 
 * To do that it first fills the fops structure with valid call 
 * back functions
 * 
 * After we register with the Linux Kernel the kernel gives back
 * a driver id which is stored in char_device_id
 * 
 *

 * */
static int char_device_id;
static struct cdev *veda_cdev;
dev_t mydev;
//static struct serio_driver kb_drv;

static wait_queue_head_t kb_queue;

int wtevnt;
static unsigned char some_data = 100;
static unsigned char up_code;

static unsigned char key_codes[10]={82,79,80,81,75,76,77,71,72,73};
/* scancodes of 0,1,2,3,4,5,6,7,8,9 on numeric pad */

static unsigned char key_ascii_codes[10]={49,50,51,52,53,54,55,56,57,58};

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
static struct class_simple *veda_class=NULL;//udev support
#else
static struct class *veda_class=NULL;//udev support
#endif

static int init_char_device(void)
{
	unsigned int ret;

	char_device_file_ops.owner = THIS_MODULE,
	char_device_file_ops.read = char_device_read;
	char_device_file_ops.open = char_device_open;
	char_device_file_ops.release = char_device_release;
	
        ret=alloc_chrdev_region(&mydev,0,1,"mykb");

        char_device_id= MAJOR(mydev);//extract major no

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
        veda_cdev->ops= &char_device_file_ops;

        ret=cdev_add(veda_cdev,mydev,1);
        if( ret < 0 ) {
                printk("Error registering device driver\n");
                return ret;
        }
        printk("\nDevice Registered with MAJOR NO[%d]\n",char_device_id);
	
      if(request_irq(KB_INT,kb_interrupt,IRQF_SHARED, "mykb",(void *)&some_data)){
                printk(KERN_ERR "mykb: cannot register IRQ %d\n", 8);
                return -EIO;
        }
	init_waitqueue_head(&kb_queue);
        printk("mykb interrupt registered\n");

	return 0;
}

/**
 * This function should neatly unregister itself and return
 * */
static void exit_char_device(void)
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
	printk("\n Module Successfully Un-registered\n");
}

#define SUCCESS 0
/**
 * This function is called when a user wants to use this device
 * and has called the open function. 
 *
 * The function will keep a count of how many people 
 * tried to open it and increments it each time
 * this function is called
 *
 * The function prints out two pieces of information
 * 1. Number of times open() was called on this device
 * 2. Number of processes accessing this device right now
 *
 * Return value
 * 	Always returns SUCCESS
 * */
static int char_device_open(struct inode *inode,
			    struct file  *file)
{
	static int counter = 0;
	counter++;
	printk("Number of times open() was called: %d\n", counter);
	printk("Process id of the current process: %d\n", current->pid );
	return SUCCESS;
}

/**
 * This function is called when the user program uses close() function
 * 
 * The function decrements the number of processes currently
 * using this device. This should be done because if there are no
 * users of a driver for a long time, the kernel will unload 
 * the driver from the memory.
 *
 * Return value
 * 	Always returns SUCCESS
 * */
static int char_device_release(struct inode *inode,
		            struct file *file)
{
	return SUCCESS;
}

/**
 * This function is called when the user calls read on this device
 * It reads from a 'file' some data into 'buf' which
 * is 'lbuf' long starting from 'ppos' (present position)
 * Understanding the parameters
 * 	buf  = buffer
 * 	ppos = present position
 * 	lbuf = length of the buffer
 * 	file = file to read
 * The function returns the number of bytes(characters) read.
 * */
static int char_device_read(struct file *file, 
		            char *buf,
			    size_t lbuf,
			    loff_t *ppos)
{
	int ret;
        wtevnt=0;
        wait_event_interruptible(kb_queue,wtevnt!=0);
//process can be interrupted by sending signals.
        //interrupt handler will be waking up us.
        ret = copy_to_user(buf,&up_code,1);
	return 1;
}

unsigned char key_code(unsigned char scancode){
        int i;
        for(i=0;i<10;i++){
                if(key_codes[i] == scancode )
                        return i;
        }
        return 255; //unknown key indicator
}

static irqreturn_t kb_interrupt(int irq, void *dev_id)
{
        unsigned char scancode;
        unsigned char kc;
        scancode = read_kbd_input();
        kc = key_code(scancode);
/* if key is know we will wake up the process otherwise we will not */
        if( kc !=255){
                up_code =key_ascii_codes[kc];
                wtevnt=1;
                wake_up_interruptible(&kb_queue);
        }
        return IRQ_HANDLED;
}

