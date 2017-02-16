/*
 * Author:Team veda
 * Developed and tested with: Linux kernel version 2.6.10
 * Tested with: Linux kernel version 2.6.29 also
 */
 
#ifndef __KERNEL__
	#define __KERNEL__
#endif

#ifndef MODULE
	#define MODULE
#endif

#define EXPORT_SYMTAB
#define SUCCESS 0

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

static __init int myinit(void)
{
	unsigned long j = jiffies + 10*HZ;
	printk("Try to do something for the next 10 seconds.\n");
	printk("I am putting the system off to a standstill for the\n"
	       "next 10 seconds");
	while( jiffies < j ) { 
		
                }
	printk("Now I am out of the loop");
	return -1; /* dont load the module */
}

/* exit point */
static __exit void myexit(void)
{
printk("\nModule Successfully removed");
}


MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Example");
MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);
/* entry point */
/* entry point */
