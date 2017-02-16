/* Implementation of skeleton char device driver 
Version : 1.0
Author : Team - C.
Assumption: Driver is implemented in view of a non existing device called LCD 
*/
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>    
#include <asm/uaccess.h> //copy_from/to_user
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/module.h>

#define LCD_MAJOR 190

static unsigned char inuse = 0;
 
static int nbytes;
/* we will allow only one app to access LCD at a point of time. */

int mylcd_open(struct inode *inode, struct file *filp)
{
	if(inuse)
		return -EBUSY;
	inuse = 1;// indicating this is in use.
	return 0;
}

int mylcd_release(struct inode *inode, struct file *filp)
{
	inuse = 0;
	return 0;
}

ssize_t mylcd_write(struct file *filp, const char *buf, size_t count,
		    loff_t *f_pos)
{
	char data[10];
	nbytes=copy_from_user(data,buf,count);
	printk("\n data = %s",data);
	return nbytes;

}

static struct file_operations fops = {
	write:mylcd_write,
	open: mylcd_open,
	release:mylcd_release,
};

int mylcd_init(void)
{
	int result = 0;
	inuse = 0;
	result = register_chrdev(LCD_MAJOR,"mylcd",&fops);
	return 0;
}

void mylcd_exit(void)
{

    unregister_chrdev(LCD_MAJOR, "mylcd");

}
MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("DUMMY LCD DEVICE MODULE");
MODULE_LICENSE("GPL");

module_init(mylcd_init);
module_exit(mylcd_exit);
