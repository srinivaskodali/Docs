/*
 * using Completions
 * Author:Team-c
 * Version:1.0
 * Tested with: Linux kernel version 2.6.29 also
 *
 * Code changes after 2.6.29 kernel version:
 *	 1) Function name of class_device_create changed to device_create.
 *       2) Function name of class_device_destroy changed to device_destroy.
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>  /* current and everything */
#include <linux/kernel.h> /* printk() */
#include <linux/fs.h>     /* everything... */
#include <linux/types.h>  /* size_t */
#include <linux/cdev.h>  /* size_t */
#include <linux/device.h>  /* size_t */
#include <linux/version.h>
#include <linux/completion.h>


/**
 * Instead of having init_module and cleanup_module
 * we will use the macros module_init and module_exit
 * to set the init and cleanup functions
 * */

int complete_init(void);
void complete_cleanup(void);

module_init(complete_init);
module_exit(complete_cleanup);

MODULE_LICENSE("Dual BSD/GPL");

/* Forward declaration of functions */
ssize_t complete_read (struct file *filp, char __user *buf,
			 size_t count, loff_t *pos);

ssize_t complete_write (struct file *filp, const char __user *buf, 
			 size_t count,loff_t *pos);

/* Define the mapping structure */
static struct file_operations veda_fops;


DECLARE_COMPLETION(veda);

static int veda_id;
#define CHAR_DEVICE_NAME "complete"
#define MAX_LENGTH 4000
static char veda_device_buf[MAX_LENGTH];
struct cdev *veda_cdev;//internal representation of char dev
dev_t mydev;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
static struct class_simple *veda_class=NULL;//udev support
#else
static struct class *veda_class=NULL;//udev support
#endif


ssize_t complete_read (struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
	printk(KERN_DEBUG "process %i (%s) going to sleep\n",
			current->pid, current->comm);
	wait_for_completion(&veda);
	printk(KERN_DEBUG "awoken %i (%s)\n", current->pid, current->comm);
	return 0; 
}

ssize_t complete_write (struct file *filp, const char __user *buf, size_t count,
		loff_t *pos)
{
	printk(KERN_DEBUG "process %i (%s) awakening the readers...\n",
			current->pid, current->comm);
	complete(&veda);
	return count; /* succeed, to avoid retrial */
}


int complete_init(void)
{

int i,ret;
        veda_fops.owner = THIS_MODULE;
        veda_fops.read = complete_read;
        veda_fops.write = complete_write;

        ret=alloc_chrdev_region(&mydev,0,1,"complete");

        veda_id= MAJOR(mydev);//extract major no

        /* Let's Start Udev stuff */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
        veda_class = class_simple_create(THIS_MODULE,"Veda");
        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }

        class_simple_device_add(veda_class,mydev,NULL,"complete");
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,14)
     veda_class=class_create(THIS_MODULE,"Veda");

        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }

        device_create(veda_class,NULL,mydev,NULL,"complete");
#endif

        /*Register our character Device*/
        veda_cdev= cdev_alloc();


        veda_cdev->owner=THIS_MODULE;
        veda_cdev->ops= &veda_fops;


        ret=cdev_add(veda_cdev,mydev,1);
        if( ret < 0 ) {
                printk("Error registering device driver\n");
                return ret;
        }
        printk("Device Registered with MAJOR NO[%d]\n",veda_id);

        for(i=0; i<MAX_LENGTH; i++) veda_device_buf[i] = 0;
        veda_device_buf[MAX_LENGTH] = '\0';
        return 0;
}

void complete_cleanup(void)
{

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
        class_simple_device_remove(mydev);
        class_simple_destroy(veda_class);
#else
        device_destroy(veda_class,mydev);
        class_destroy(veda_class);
#endif
        unregister_chrdev_region(mydev,1);
        cdev_del(veda_cdev);
	printk("\n Module Successfully Removed");
}

