/* 
 * using Completions 
 * Author:Team-c
 * Version:1.0
 * Tested with: Linux kernel version 2.6.29 also
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>  /* current and everything */
#include <linux/kernel.h> /* printk() */
#include <linux/fs.h>     /* everything... */
#include <linux/types.h>  /* size_t */
#include <linux/completion.h>


static int complete_major = 0;

DECLARE_COMPLETION(veda);

ssize_t complete_read (struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
	printk(KERN_DEBUG "process %i (%s) going to sleep\n",
			current->pid, current->comm);
	wait_for_completion(&veda);
	printk(KERN_DEBUG "awoken %i (%s)\n", current->pid, current->comm);
	return 0; 
}

ssize_t complete_write (struct file *filp, const char __user *buf, size_t count,
		loff_t *pos)
{
	printk(KERN_DEBUG "process %i (%s) awakening the readers...\n",
			current->pid, current->comm);
	complete(&veda);
	return count; /* succeed, to avoid retrial */
}


struct file_operations veda_fops = {
	.owner = THIS_MODULE,
	.read =  complete_read,
	.write = complete_write,
};


int complete_init(void)
{
	int result;

	/*
	 * Register your major, and accept a dynamic number
	 */
	result = register_chrdev(complete_major, "complete", &veda_fops);
	if (result < 0)
		return result;
	if (complete_major == 0)
		complete_major = result; /* dynamic */
	return 0;
}

void complete_cleanup(void)
{
	unregister_chrdev(complete_major, "complete");
}

module_init(complete_init);
module_exit(complete_cleanup);

MODULE_LICENSE("Dual BSD/GPL");
