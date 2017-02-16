/*Dep module
Author:Team-c
Version:1.0
Tested with: Linux kernel version 2.6.29 also
*/
#ifndef MODULE
        #define MODULE
#endif
#ifndef __KERNEL__
        #define __KERNEL__
#endif

#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/init.h>

extern void func(void);

static __init int myinit(void)
{
	printk(" Calling Kernel symbol \n ");
	func();
	return 0;
}

static __exit void myexit(void)
{
	printk(" cleanup invoked \n");
}
module_init(myinit);
module_exit(myexit);

/*Kernel module Comments*/
MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("DEP  MODULE");
MODULE_LICENSE("GPL");




