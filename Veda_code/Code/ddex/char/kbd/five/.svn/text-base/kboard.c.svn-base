/* Implementation of device Driver for keyboard, check Reamme.kb for 
details.
Version : 1.0
Author : Team - C.
*/

#ifndef MODULE
        #define MODULE
#endif

#ifndef __KERNEL__
        #define __KERNEL__
#endif

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>    
#include <linux/slab.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h> //copy_from/to_user
#include "kboard.h"
#include <asm/irq.h>
#include <linux/wait.h>
#include <linux/interrupt.h>

#define KB_INT  1

#include <linux/cdev.h>
#include <linux/device.h>

MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Keyboard Device Driver - Test");
MODULE_LICENSE("GPL");

static int kb_init(void);
static void kb_exit(void);

module_init(kb_init);
module_exit(kb_exit);

/* Forward declaration of functions */
int kb_open(struct inode *inode,
                            struct file  *file);
int kb_release(struct inode *inode,
                            struct file *file);
ssize_t kb_read(struct file *file,
                            char *buf,
                            size_t lbuf,
                            loff_t *ppos);

static irqreturn_t kb_interrupt(int,void *,struct pt_regs *);

/* Define the mapping structure */
static struct file_operations kb_file_ops;

struct cdev *veda_cdev;
dev_t mydev;
static unsigned char inuse;
static unsigned int char_device_id;
static unsigned char some_data = 100;

static wait_queue_head_t kb_queue;

static unsigned char up_code;

static unsigned char key_codes[10]={82,79,80,81,75,76,77,71,72,73};
/* scancodes of 0,1,2,3,4,5,6,7,8,9 on numeric pad */

static unsigned char key_ascii_codes[10]={49,50,51,52,53,54,55,56,57,58};

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
static struct class_simple *veda_class=NULL;//udev support
#else
static struct class *veda_class=NULL;//udev support
#endif

int kb_open(struct inode *inode, struct file *filp)
{
	if(inuse)
		return -EBUSY;
	inuse = 1;// indicating this is in use.
	return 0;
}

int kb_release(struct inode *inode, struct file *filp)
{
	inuse = 0;
	return 0;
}

int evnt;

ssize_t kb_read(struct file *filp,char *buf, size_t count,
		    loff_t *f_pos)
{
	int ret;
	evnt=0;	
	wait_event(kb_queue,evnt==1);
	
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


static irqreturn_t kb_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	unsigned char scancode;
	unsigned char kc;
	scancode = read_kbd_input();
	kc = key_code(scancode);
/* if key is know we will wake up the process otherwise we will not */
	if( kc !=255){
		up_code =key_ascii_codes[kc];
		evnt=1;
		wake_up(&kb_queue);
	}
return 0;
}


int kb_init(void)
{	
	unsigned int ret;
	inuse = 0;

	ret = alloc_chrdev_region(&mydev,0,1,"mykb");
	char_device_id = MAJOR(mydev);

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

        class_device_create(veda_class,mydev,NULL,"mykb");
#endif


 /*Register our character Device*/
	veda_cdev = cdev_alloc();

	veda_cdev -> owner = THIS_MODULE;
	veda_cdev -> ops = &kb_file_ops;

	ret = cdev_add(veda_cdev, mydev, 1);

	init_waitqueue_head(&kb_queue);	


	 if( ret < 0 ) {
	 printk("Error registering device driver\n");
	  return ret;
 }
    

	printk("\n Device Regitered with id : %d",char_device_id);	

if(request_irq(KB_INT,kb_interrupt,SA_SHIRQ, "mykb",(void *)&some_data)){
		printk(KERN_ERR "mykb: cannot register IRQ %d\n", 8);
		return -EIO;
	}
	printk("\n mykb interrupt registered\n");
	return 0;
}


void kb_exit(void)
{
	free_irq(KB_INT,&some_data);
	
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
        class_simple_device_remove(mydev);
        class_simple_destroy(veda_class);
#else
        class_device_destroy(veda_class,mydev);
        class_destroy(veda_class);
#endif

	unregister_chrdev_region(mydev,1);
	cdev_del(veda_cdev);
	printk("\n Module Successfully Un-registered\n");
	
}
