/* This shows how to write async char device driver
** Team: Veda
** Version: 1.0
 * Changes after 2.6.29 Version:
 *  1.device_create()
 *  2.device_destroy()
 */

//#ifndef __KERNEL__
//	#define __KERNEL__
//#endif
//
//#ifndef MODULE
//	#define MODULE
//#endif

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/version.h>
#include "char_device.h"

MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");

/**
 * Instead of having init_module and cleanup_module
 * we will use the macros module_init and module_exit
 * to set the init and cleanup functions
 * */

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
static int char_device_ioctl(struct inode *inode,
			    struct file *filp,
			    unsigned int cmd,
			    unsigned long arg);
static int char_device_fasync(int fd, 
			    struct file *filp,
			    int mode);
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
 * The name of the device  would be CHAR_DEVICE_NAME = "chrdev"
 *
 * */
static int char_device_id;
static unsigned int length = 4000;
#define CHAR_DEVICE_NAME "chrdev"
#define MAX_LENGTH length
static char *char_device_buf;
static struct cdev *veda_cdev;
dev_t mydev;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
static struct class_simple *veda_class=NULL;//udev support
#else
static struct class *veda_class=NULL;//udev support
#endif

static struct fasync_struct *async_struct = 0;

static int init_char_device(void)
{
	unsigned int i,ret;

	char_device_buf = (char *)kmalloc(MAX_LENGTH*sizeof(char), 
					  GFP_KERNEL);
	if( !char_device_buf ) return -ENOSPC;
	
	char_device_file_ops.owner = THIS_MODULE;
	char_device_file_ops.read = char_device_read;
	char_device_file_ops.write = char_device_write;
	char_device_file_ops.open = char_device_open;
	char_device_file_ops.release = char_device_release;
	char_device_file_ops.ioctl = char_device_ioctl;
	char_device_file_ops.fasync = char_device_fasync;
	   ret=alloc_chrdev_region(&mydev,0,1,"veda_cdrv");

        char_device_id= MAJOR(mydev);//extract major no

        /* Let's Start Udev stuff */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,14)
        veda_class = class_simple_create(THIS_MODULE,"Veda");
        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }

        class_simple_device_add(veda_class,mydev,NULL,"veda_cdrv");
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,14)
        veda_class = class_create(THIS_MODULE,"Veda");
        if(IS_ERR(veda_class)){
                printk(KERN_ERR "Error registering veda class\n");
        }

        device_create(veda_class,NULL,mydev,NULL,"veda_cdrv");
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
        printk("Device Registered with MAJOR NO[%d]\n",char_device_id);

        for(i=0; i<MAX_LENGTH; i++) char_device_buf[i] = 0;
        return 0;
}

/**
 * This function should neatly unregister itself and return
 * */
static void exit_char_device(void)
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
	printk("\n Module Successfully Un-registered");
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
	int nbytes;
	int bytes_to_do;
	
	if( lbuf > MAX_LENGTH ) bytes_to_do = MAX_LENGTH;
	else bytes_to_do = lbuf;
	
	*ppos = 0;
	if( char_device_buf[0] == 0 ) {
		return 0;
	}
	/* resume after sleep or normal operation */
	nbytes = bytes_to_do - 
		 copy_to_user( buf, /* to */
			       char_device_buf, /* from */
			       bytes_to_do ); /* how many bytes */
	return nbytes;
}

/**
 * This function is called when the user calls write on this device
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
	
	if( lbuf > MAX_LENGTH ) bytes_to_do = MAX_LENGTH;
	else bytes_to_do = lbuf;
	
	*ppos = 0;
	nbytes = bytes_to_do -
	         copy_from_user( char_device_buf, /* to */
				 buf, /* from */
				 bytes_to_do ); /* how many bytes */
	/* inform the asynchronous readers */
	if( async_struct ) {
		printk("Sending SIGIO");
		kill_fasync(&async_struct, SIGIO, POLL_IN);
	}
		
	return nbytes;
}

static int char_device_ioctl(struct inode *inode,
			    struct file *filp,
			    unsigned int cmd,
			    unsigned long arg)
{
	unsigned int i, size;
	char *new_buf;
	char c;
	int ret=SUCCESS;
	
	if( _IOC_TYPE(cmd) != CHAR_MAGIC ) return -ENOTTY;
	if( _IOC_NR(cmd) > CHAR_MAX_CMDS ) return -ENOTTY;
	
	if( _IOC_DIR(cmd) & _IOC_READ )
		if( !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd) ) )
			return -EFAULT;
	if( _IOC_DIR(cmd) & _IOC_WRITE )
		if( !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd) ) )
			return -EFAULT;
	
	/* sounds ok lets continue */
	switch(cmd) {
	
	case CHAR_FILL_ZERO: 
		for(i=0; i<MAX_LENGTH; i++) char_device_buf[i] = 0;
		break;
	
	case CHAR_FILL_CHAR:
		if (!(copy_from_user( &c, (char *)arg, sizeof(char) ) ) )
		{
			ret = -EFAULT;
			break;
		}
		for(i=0; i<MAX_LENGTH; i++) char_device_buf[i] = c;
		break;
		
	case CHAR_SET_SIZE:
		if( !(copy_from_user( &size, (unsigned int*)arg, 
				sizeof(unsigned int) )))
		{
			ret = -EFAULT;	
			break;
		}	
		
		new_buf = (char *)kmalloc( size*sizeof(char),
					   GFP_KERNEL );
		if( !new_buf ) return -ENOSPC;
		kfree( char_device_buf );
		char_device_buf = new_buf;
		MAX_LENGTH = size;
		for(i=0; i<MAX_LENGTH; i++) char_device_buf[i] = 0;
		filp->f_pos = 0;
		break;
	
	case CHAR_GET_SIZE:
		if (!(copy_to_user( (unsigned int*)arg, 
			&(MAX_LENGTH), sizeof(unsigned int) )))
		{
			ret = -EFAULT;
			break;
		}
		break;
	}
	
	return ret;
}

static int char_device_fasync(int fd, 
			    struct file *filp,
			    int mode)
{
	printk("Calling fasync in driver");
	return fasync_helper(fd, filp, mode, &async_struct);
}
/* End of code */

