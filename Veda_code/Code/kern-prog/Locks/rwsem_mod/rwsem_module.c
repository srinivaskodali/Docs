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
#include <linux/rwsem.h>


int global=10;
struct rw_semaphore my_semaphore;
EXPORT_SYMBOL_GPL(global);
EXPORT_SYMBOL_GPL(my_semaphore);

int myinit(void)
{
	init_rwsem(&my_semaphore);
printk("\n Module Inserted");
printk("\n Global Value =%d Count=%ld\n",global,my_semaphore.count);
      return 0;

}
void myexit(void)
{
printk("\n Module Removed \n");
}

MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);

