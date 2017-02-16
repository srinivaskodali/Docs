/*Module exporting choosen symbols
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
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/stat.h>
#include<linux/moduleparam.h>

static int val=0; 

module_param(val,int,S_IRUGO);//read only
//module_param(val,int,S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(val, "INTIALISE ME AT INSERTION TIME");
MODULE_SUPPORTED_DEVICE("NULL");
void func(void);
void func1(void);

void func()
{
	printk("func invoked\n ");
	printk(" val = %d",val);
}

void func1()
{
	printk(" func 1 invoked\n");
}	

int myinit(void)
{
	printk(" module inserted\n ");
	func();
	return 0;
}

void myexit(void)
{
	printk(" module removed\n ");
}

module_init(myinit);
module_exit(myexit);

/*Kernel module Comments*/
MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("FIRST MODULE");
MODULE_LICENSE("DUAL BSD/GPL");
//All module param types are defined in <linux/moduleparam.h>
