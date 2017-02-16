/*First module program
Author:Team Veda
Version:1.0
Tested with: Linux kernel version 2.6.29 also
*/
#include<linux/module.h> //kmod interface 
#include<linux/version.h>// kernel version stamp
#include<linux/kernel.h>// resolve kernel symbol calls
#include<linux/init.h>

void func(void);

int val=300;

void func()
{
	printk("func invoked\n ");
	printk(" val = %d",val);
}	

int init_mod(void)
{
	printk("module inserted\n ");
	return 0;
}

void cleanup_mod(void)
{
	printk("module removed\n ");
}

module_init(init_mod);
module_exit(cleanup_mod);

/*Kernel module Comments*/
MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("FIRST MODULE");
MODULE_LICENSE("GPL");
