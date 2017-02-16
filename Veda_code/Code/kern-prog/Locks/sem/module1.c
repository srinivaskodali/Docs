/* Shows Usage of Semaphores in Modules
Author;Team-c
Version:1.0
Tested with: Linux kernel version 2.6.29 also

Code changes after 2.6.29 kernel version:
	1)Used #include <linux/semaphore.h> instead of #include<asm/semaphore.h>
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
#include <linux/semaphore.h>

static  struct semaphore my_semaphore;
int get_semaphore(void);
void leave_semaphore(void);

EXPORT_SYMBOL_GPL(get_semaphore);
EXPORT_SYMBOL_GPL(leave_semaphore);

int myinit(void)
{
	init_MUTEX( &my_semaphore );
       
	printk("\n\nModule1: I have the semaphore\n");
	
	down( &my_semaphore );

	printk("Getting  the semaphore and the count is:%d\n",my_semaphore.count);
	
	up( &my_semaphore );
	
	printk("Released semaphore and count now is:%d\n",my_semaphore.count);
	printk("\nModule1: Exported semaphore [my_semaphore]\n\n");
	return 0;
}

void myexit(void)
{
	printk("\n\nSemaphore Destroyed\n\n");
}

int get_semaphore(void)
{
	return down_trylock( &my_semaphore );
}

void leave_semaphore(void)
{
	up( &my_semaphore );
	
}
MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);


