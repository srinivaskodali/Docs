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
#include <linux/slab.h>
#include <linux/semaphore.h>



extern int get_semaphore(void);
extern void leave_semaphore(void);
/**
 * We would like to use SIGNAL and WAIT macros instead of down and up
 * primitives provided by the Linux headers
 *
 * SIGNAL primitive says that the semaphore usage is finished
 * WAIT   primitive says that the current process should wait for 
 * 	  semaphore to be available
 * 	  
 * */

#define WAIT()      get_semaphore()
#define SIGNAL()    leave_semaphore()


static int myinit(void)
{
	printk("\nModule3: Waiting for semaphore\n");
	if( WAIT() ) {
		printk("Module3: Not got semaphore\n");
		return -1;
	}
	printk("Module3: Got semaphore now\n");
	return 0;
}

static void myexit(void)
{
	SIGNAL();
	printk("\n Module3 says bye");
}
module_init(myinit);
module_exit(myexit);
MODULE_LICENSE("GPL");

