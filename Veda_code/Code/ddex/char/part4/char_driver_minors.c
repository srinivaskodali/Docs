#ifndef __KERNEL__
	#define __KERNEL__
#endif

#ifndef MODULE
	#define MODULE
#endif

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
#include <linux/mutex.h>
#include <linux/kdev_t.h>
#include <linux/version.h>

#include "veda_char_device.h"

MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");


/**
 * Instead of having init_module and cleanup_module
 * we will use the macros module_init and module_exit
 * to set the init and cleanup functions
 *
 * Changes after 2.6.29 Version:
 *  1.device_create()
 *  2.device_destroy()
 *  3.usage of Mutex instead of Semaphore(as mutex occupies less
 *   memory,slightly faster and has better scalability for contended workloads than semaphore)
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
static int char_device_write(struct file *file,
		            const char *buf,
			    size_t lbuf,
			    loff_t *ppos);
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
 * The name of the device  would be CHAR_DEVICE_NAME = "veda_cdrv"
 *

 * */
static int char_device_id;
static unsigned int length = 500;
#define CHAR_DEVICE_NAME "veda_cdrv"
#define MAX_LENGTH length
static char *char_device_buf_minor0;
static char *char_device_buf_minor1;
static char *char_device_buf_minor2;
static struct cdev *veda_cdev;
dev_t mydev;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
static struct class_simple *veda_class=NULL;//udev support
#else
static struct class *veda_class=NULL;//udev support
#endif


/* Now create wait-queues and semaphores for the minors*/
static wait_queue_head_t veda_queue0;
static wait_queue_head_t veda_queue1;
static wait_queue_head_t veda_queue2;

struct mutex vmut0;
struct mutex vmut1;
struct mutex vmut2;
static int init_char_device(void)
{
	unsigned int i,ret;

	char_device_buf_minor0 = (char *)kmalloc(MAX_LENGTH*sizeof(char), 
					  GFP_KERNEL);
	char_device_buf_minor1 = (char *)kmalloc(MAX_LENGTH*sizeof(char), 
					  GFP_KERNEL);
	char_device_buf_minor2 = (char *)kmalloc(MAX_LENGTH*sizeof(char), 
					  GFP_KERNEL);

	if( !char_device_buf_minor0 ) return -ENOSPC;
	if( !char_device_buf_minor1 ) return -ENOSPC;
	if( !char_device_buf_minor2 ) return -ENOSPC;
	
	char_device_file_ops.owner = THIS_MODULE,
	char_device_file_ops.read = char_device_read;
	char_device_file_ops.read = char_device_read;
	char_device_file_ops.write = char_device_write;
	char_device_file_ops.open = char_device_open;
	char_device_file_ops.release = char_device_release;
	
	
        ret=alloc_chrdev_region(&mydev,0,3,"veda_cdrv");

        char_device_id= MAJOR(mydev);//extract major no

        /* Let's Start Udev stuff */
        
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
        veda_class = class_simple_create(THIS_MODULE,"Veda");
        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }
	for(i=0;i<3;i++)
        class_simple_device_add(veda_class,MKDEV(char_device_id,i),NULL,"veda_cdrv",i);
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,14)

	veda_class = class_create(THIS_MODULE,"Veda");
        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }

	for(i=0;i<3;i++)
        device_create(veda_class,NULL,MKDEV(char_device_id,i),NULL,"veda_cdrv");
#endif
        /*Register our character Device*/
        veda_cdev= cdev_alloc();


        veda_cdev->owner=THIS_MODULE;
        veda_cdev->ops= &char_device_file_ops;


	for(i=0;i<3;i++)
        	ret=cdev_add(veda_cdev,MKDEV(char_device_id,i),3);
        if( ret < 0 ) {
                printk("Error registering device driver\n");
                return ret;
        }
        printk("Device Registered with MAJOR NO[%d]\n",char_device_id);
	
	for(i=0; i<MAX_LENGTH; i++) char_device_buf_minor0[i] = 0;
	for(i=0; i<MAX_LENGTH; i++) char_device_buf_minor1[i] = 0;
	for(i=0; i<MAX_LENGTH; i++) char_device_buf_minor2[i] = 0;
	init_waitqueue_head( &veda_queue0 );
	init_waitqueue_head( &veda_queue1 );
	init_waitqueue_head( &veda_queue2 );
	mutex_init(&vmut0);
	mutex_init(&vmut1);
	mutex_init(&vmut2);
	return 0;
}

/**
 * This function should neatly unregister itself and return
 * */
static void exit_char_device(void)
{
	int i;
	kfree(char_device_buf_minor0);
	kfree(char_device_buf_minor1);
	kfree(char_device_buf_minor2);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
	for(i=0;i<3;i++)
        class_simple_device_remove(MKDEV(char_device_id,i));
        class_simple_destroy(veda_class);
#else
	for(i=0;i<3;i++)
	device_destroy(veda_class,MKDEV(char_device_id,i));
        class_destroy(veda_class);
#endif
	for(i=0;i<3;i++)
        unregister_chrdev_region(MKDEV(char_device_id,i),0);
        cdev_del(veda_cdev);
	printk("\n Module Removed");
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
	static int nbytes;
	static int bytes_to_do;
	static int ret,ret1;
	int minor=-1;
	struct inode *inode;

	inode = file->f_dentry->d_inode;
	// Grab the minor. So that we work with the device which has a call.
	minor = iminor(inode);
	printk("\n MInor  = %d",minor);
	switch(minor)
	{
	case 0:
	if(atomic_read(&vmut0.count))
	{
	if( lbuf > MAX_LENGTH ) bytes_to_do = MAX_LENGTH;
	else bytes_to_do = lbuf;
	
	*ppos = 0;
	if( char_device_buf_minor0[0] == 0 ) {
		/* data has not arrived yet put the process 
		   to sleep */
		wait_event(veda_queue0,char_device_buf_minor0[0] != 0);	
	}
	/* resume after sleep or normal operation */
	ret1 = mutex_lock_killable(&vmut0);
	ret = nbytes = bytes_to_do - 
		 copy_to_user( buf, /* to */
			       char_device_buf_minor0, /* from */
			       bytes_to_do ); /* how many bytes */
	mutex_unlock(&vmut0);
	}
	else
		ret = -EACCES;  // Making the read operation non-re-entrant
	break;

	case 1:
	if(atomic_read(&vmut1.count))
	{
	if( char_device_buf_minor1[0] == 0 ) {
		/* data has not arrived yet put the process 
		   to sleep */
		wait_event(veda_queue1,char_device_buf_minor1[0] != 0);	
	}
	/* resume after sleep or normal operation */
	ret1 = mutex_lock_killable(&vmut1);
	ret = nbytes = bytes_to_do - 
		 copy_to_user( buf, /* to */
			       char_device_buf_minor1, /* from */
			       bytes_to_do ); /* how many bytes */
	mutex_unlock(&vmut1);
	}
	else
		ret = -EACCES;  // Making the read operation non-re-entrant
	break;

	case 2:
	if(atomic_read(&vmut2.count))
	{
	if( char_device_buf_minor2[0] == 0 ) {
		/* data has not arrived yet put the process 
		   to sleep */
		wait_event(veda_queue2,char_device_buf_minor2[0] != 0);	
	}
	/* resume after sleep or normal operation */
	ret1 = mutex_lock_killable(&vmut2);
	ret = nbytes = bytes_to_do - 
		 copy_to_user( buf, /* to */
			       char_device_buf_minor2, /* from */
			       bytes_to_do ); /* how many bytes */
	mutex_unlock(&vmut2);
	}
	else
		ret = -EACCES;  // Making the read operation non-re-entrant
	break;

	default:
		printk("\n Supports only 3 minors");
	}

	return ret;
}

/**
 * ``This function is called when the user calls write on this device
 * It writes into 'file' the contents of 'buf' starting from 'ppos'
 * up to 'lbuf' bytes.
 * Understanding the parameters
 * 	buf  = buffer
 * 	file = file to write into
 * 	lbuf = length of the buffer
 * 	ppos = present position pointer
 * The function returs the number of characters(bytes) written
 * */
static int char_device_write(struct file *file,
		            const char *buf,
			    size_t lbuf,
			    loff_t *ppos)
{
	int nbytes; /* Number of bytes written */
	int bytes_to_do; /* Number of bytes to write */
	static int ret,ret1;
	int read_minor=-1;

	struct inode *inode;

	inode = file->f_dentry->d_inode;

	// Grab the minor. So that we work with the device which has a call.
        read_minor = iminor(inode);	
	switch(read_minor)
	{
	case 0:
	if(atomic_read(&vmut0.count))
	{
	if( lbuf > MAX_LENGTH ) bytes_to_do = MAX_LENGTH;
	else bytes_to_do = lbuf;
	
	*ppos = 0;
	ret1 = mutex_lock_killable(&vmut0);
	       ret = copy_from_user( char_device_buf_minor0, /* to */
				 buf, /* from */
				 bytes_to_do ); /* how many bytes */
	mutex_unlock(&vmut0);
	/* wake up readers that are waiting for this data */
	wake_up( &veda_queue0 );
	}
	else
		ret=-EACCES;	
	break;

	case 1:
        if(atomic_read(&vmut1.count))
        {
        if( lbuf > MAX_LENGTH ) bytes_to_do = MAX_LENGTH;
        else bytes_to_do = lbuf;

        *ppos = 0;
	ret1 = mutex_lock_killable(&vmut1);
        ret = nbytes = bytes_to_do -
                 copy_from_user( char_device_buf_minor1, /* to */
                                 buf, /* from */
                                 bytes_to_do ); /* how many bytes */
	mutex_unlock(&vmut1);
        /* wake up readers that are waiting for this data */
        wake_up( &veda_queue1 );
        }
        else
                ret=-EACCES;
	break;

	case 2:
        if(atomic_read(&vmut2.count))
        {
        if( lbuf > MAX_LENGTH ) bytes_to_do = MAX_LENGTH;
        else bytes_to_do = lbuf;

        *ppos = 0;
	ret1 = mutex_lock_killable(&vmut2);
        ret = nbytes = bytes_to_do -
                 copy_from_user( char_device_buf_minor2, /* to */
                                 buf, /* from */
                                 bytes_to_do ); /* how many bytes */
	mutex_unlock(&vmut2);
        /* wake up readers that are waiting for this data */
        wake_up( &veda_queue2 );
        }
        else
                ret=-EACCES;
	break;
	
	default:
		printk("\n Supports only 3 minors");	
	}

	return ret;
}

/* End of code */


/* Notes:  From kernel 2.6 onwards the use of sleep_on_* functions is deprecated. Instead the\
	   usage of wait_event_*  macros are encouraged. These macros are defined in
	   linux/wait.h
*/		
