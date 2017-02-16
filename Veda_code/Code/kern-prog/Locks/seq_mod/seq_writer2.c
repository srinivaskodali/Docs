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
#include <linux/seqlock.h>
extern int global;
extern seqlock_t lock;
static int myinit(void)
{
	printk("\nWriter2: I am in Write mode");
	printk("\nI am changing the value");
	if((lock.sequence)%2==0)
	{
	write_seqlock(&lock);
	global=30;
	printk("\n The GLOBAL value= %d\n",global);
	}
	else
	{
	printk("\n Sorry, It's Already locked\n");
	return -1;
	}
	return 0;
}

static void myexit(void)
{
	printk("\n Writer2: says bye\n");
	write_sequnlock(&lock);
}
module_init(myinit);
module_exit(myexit);
MODULE_LICENSE("GPL");

