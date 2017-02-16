/* 
 * atomic variables   
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/atomic.h>


static int init_atomic(void);
static void exit_module(void);

module_init(init_atomic);
module_exit(exit_module);

static int init_atomic(void)
{
  atomic_t av = ATOMIC_INIT(1);
  printk("first value of av is = %d\n",atomic_read(&av));
  
   atomic_add(2,&av);
   printk("after adding 2 to av = %d \n",atomic_read(&av));
 
  atomic_sub(2,&av);
  printk("after subtracting 2 from av = %d \n",atomic_read(&av));
 
  atomic_inc(&av);
  printk("after incrementing the av = %d\n",atomic_read(&av));
  
  return 0;
}
static void exit_module(void)
{
	printk("\nModule successfully unregistered\n");
}

