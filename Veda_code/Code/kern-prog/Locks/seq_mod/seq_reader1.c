/* Shows Usage of Semaphores in Modules
Author;Team-c
Version:1.0
Tested with: Linux kernel version 2.6.29 also
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

int seq;
extern int global;
extern seqlock_t lock;

int myinit(void)
{
printk("\n Module Inserted\n");
while (read_seqretry(&lock,seq)%2 == 0)
{

	seq=read_seqbegin(&lock);	
	printk("\n Iam in Read Mode ");
	printk("\n Global Value =%d  lock.seq=%d\n",global,lock.sequence);
	break;
} 
  
      return 0;

}
void myexit(void)
{
printk("\n Module Removed \n");
}

MODULE_LICENSE("GPL");
module_init(myinit);
module_exit(myexit);

