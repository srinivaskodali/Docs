/*
 * Shows the use of kernel JIFFIES
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
#include <linux/jiffies.h>
#include <asm/param.h>


int  init_module_jiff(void);
void exit_module_jiff(void);

module_init(init_module_jiff);
module_exit(exit_module_jiff);


/* entry point */
 int init_module_jiff(void)
{
	unsigned long seconds_started, hours_started, min_started;

	printk("Jiffies Value: INIT: %ld\n", jiffies);
	seconds_started = jiffies/100ul;
	min_started = seconds_started/60;
	hours_started = min_started/60;
	printk("Seconds = %ld, Hours = %ld, Minutes = %ld\n", 
		seconds_started, hours_started, min_started);
	return SUCCESS;
}

/* exit point */
  void exit_module_jiff(void)
{
	unsigned long seconds_started, hours_started, min_started;
	printk("Jiffies Value: CLEANUP: %ld\n", jiffies);
	seconds_started = jiffies/1000ul;
	min_started = seconds_started/60;
	hours_started = min_started/60;
	printk("Seconds = %ld, Hours = %ld, Minutes = %ld\n", 
		seconds_started, hours_started, min_started);
}


MODULE_AUTHOR("Team Veda");
MODULE_DESCRIPTION("Example on jiffies");
MODULE_LICENSE("GPL");
