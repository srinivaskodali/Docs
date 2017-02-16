/*
 * shows usage of linked lists in Modules
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>

/**
This is the list head. It is a pointer to the linked list rather
the first element in the linked list.
*/
struct list_head MY_list;

/**
MY_list is declared as the list head
*/
LIST_HEAD( MY_list );


/**
This is how each node in the linked list looks like.
*/
struct MY_struct {
	struct list_head MY_s_list;
	int value;
};

/**
This function is called when the module is loaded into the memory.
The function adds 20 numbers into the linked list. 
*/
int  myinit(void)
{
	struct MY_struct *ls;
	int i;
	/* Adding elements on to the list */
	for(i=0; i<20; i++) {
		ls = (struct MY_struct*)kmalloc(sizeof( struct MY_struct ),GFP_KERNEL );
		printk("%d th element is inserted \n",i);
		ls->value = i;
		list_add(&ls->MY_s_list, &MY_list);
	}
	printk("\n\n\nInserted 20 elements into the list.\n");
	printk("The list will be displayed while unloading this module\n\n\n");
	return 0;
}

/**
The function is called when the module is unloaded from the memory.
The function lists out the 20 numbers that was previously inserted.
*/
void  myexit(void)
{
struct MY_struct *list;
        /* list_for_each_entry(), iterates over given list */
	list_for_each_entry(list, &MY_list,MY_s_list )
	printk("Found number: %d\n", list->value );
}
module_init(myinit);
module_exit(myexit);

MODULE_AUTHOR("Team Veda");
MODULE_LICENSE("GPL");

