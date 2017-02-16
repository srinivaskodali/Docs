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
	printk("\nWriter1: I am in Write mode\n");
	printk("\nI am changing the value\n");
	if((lock.sequence)%2==0)
	{
	write_seqlock(&lock);
	global=20;
	printk("\n The GLOBAL value= %d lock.seq %d\n",global,lock.sequence);
	}
	else
	{
	printk("\n Sorry,It's Already locked\n");
	return -1;
	}
	return 0;
}

static void myexit(void)
{
	printk("\n Writer1:  says bye\n");
	write_sequnlock(&lock);
}
module_init(myinit);
module_exit(myexit);
MODULE_LICENSE("GPL");

