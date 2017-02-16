#ifndef __KERNEL__
	#define __KERNEL__
#endif

#ifndef MODULE
	#define MODULE
#endif

#define EXPORT_SYMTAB

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/rwsem.h>
extern int global;
extern struct rw_semaphore my_semaphore;
static int myinit(void)
{
	printk("\nWriter1: I am in Write mode\n");
	printk("\nI am changing the value\n");
	if(my_semaphore.count==0)
	{
		down_write(&my_semaphore);
		global=20;
		printk("\n The Changed Value= %d\n",global);
	}
	else
	{
	printk("\n Sorry, It's already locked\n");
	return -1;
	} 
	return 0;
}

static void myexit(void)
{
	up_write(&my_semaphore);
	printk("\n Writer1:  says bye\n");
}
module_init(myinit);
module_exit(myexit);
MODULE_LICENSE("GPL");

