/*
 * Shows Usage of Semaphores in Modules
 * Author:Team-c
 * Version:1.0
 * Tested with: Linux kernel version 2.6.29 also
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
#include <linux/seqlock.h>


int global=10;
seqlock_t lock=SEQLOCK_UNLOCKED;

EXPORT_SYMBOL(global);
EXPORT_SYMBOL(lock);

int myinit(void)
{
	printk("\n Module Inserted");
	printk("\n Global Value =%d lock.seq=%d\n",global,lock.sequence);
  
      return 0;

}
void myexit(void)
{
printk("\n Module Removed \n");
}

MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);

