/* Shows Usage of Semaphores in Modules
Author;Team-c
Version:1.0
Tested with: Linux kernel version 2.6.29 also
*/

#ifndef __KERNEL__
	#define __KERNEL__
#endif

#ifndef MODULE
	#define MODULE
#endif

#define EXPORT_SYMTAB


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/rwsem.h>

extern int global;
extern struct rw_semaphore my_semaphore;

int myinit(void)
{
printk("\n Module Inserted\n");
down_read(&my_semaphore);
printk("\n I am Reader1\n");
printk("\nReading Global value=%d\n",global);
//up_read(&my_semaphore);
return 0;

}
void myexit(void)
{
up_read(&my_semaphore);
printk("\n Reader1 Module Removed \n");
}

MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);

