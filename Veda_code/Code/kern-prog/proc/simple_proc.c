/*Writing to proc: Dumps the hardware time in /proc/hrtime
 Author:Team C
Version:1.0   
 */
#ifndef  __KERNEL__
	#define __KERNEL__
#endif 

#ifndef  MODULE
	#define MODULE 
#endif 


#include <linux/kernel.h>  /* printk level */
#include <linux/init.h>  /* printk level */
#include <linux/module.h> 
#include <linux/proc_fs.h> /* proc API */
#include <linux/rtc.h>

MODULE_DESCRIPTION("simple proc example");
MODULE_LICENSE("GPL");
/* /proc/hrtime "file-descriptor" */
struct proc_dir_entry *proc_hrtime,*proc_root;

extern unsigned long get_cmos_time(void);

int dump_stuff(char *page,char **start, off_t off, int count,int *eof, void *data)
{
    int size = 0;
	printk("in read callback");
    
	size+=sprintf(page+size,"HR-Time:%llu\n",(unsigned long long)get_cmos_time());

	return(size);
}

int proc_module(void) 
{
	/* set up a proc dir-entry in /proc */
	proc_hrtime = create_proc_entry("hrtime", 0, proc_root);

	/* assign the read method of /proc/hrtime to dump the number */
	proc_hrtime->read_proc = dump_stuff;
//	proc_hrtime->owner = THIS_MODULE;
	return 0;
}

void 
proc_exit(void) 
{
	/* remove the proc entry */
    remove_proc_entry("hrtime", proc_root);
	printk("\n OUT OF HERE\n");
}

module_init(proc_module);
module_exit(proc_exit);
