/*
This module creates a pseudo-file (named '/proc/mm') which
shows some info from a task's memory-management structure.

NOTE: Written and tested with Linux kernel version 2.6.10.

Author: ALLAN CRUSE
Version: 1.0
Tested with: Linux kernel version 2.6.29 also

Code changes after 2.6.29 kernel version:
        1) In #include<linux/mm_types.h>, member of 'struct page'(unsigned long page_flags_t)
           is replaced with unsigned long flags.
        2) In #include <linux/proc_fs.h>, function name of create_proc_info_entry() is changed
           to create_proc_entry()(function to set up a proc dir-entry in /proc)
        3) create_proc_entry() is taking 3 arguments only instead of 4(argument get_info_t,
           which takes information and pass it to the entry created in proc dir is removed).
        4) As get_info_t is removed, assign the read method of created proc entry to dump the information.
*/

#include <linux/module.h>	// for init_module() 
#include <linux/proc_fs.h>	// for create_proc_read_entry() 
#include <linux/sched.h>

/* /proc/mm "file-descriptor" */
struct proc_dir_entry *mm_info;

int my_get_info( char *buf, char **start, off_t off, int count )
{
	struct task_struct	*tsk = current;
	struct mm_struct	*mm = tsk->mm;
	int			len;

	len = sprintf( buf, "\nInfo from the Memory Management structure " );
	len += sprintf( buf+len, "for task \'%s\' ", tsk->comm );
	len += sprintf( buf+len, "(pid=%d) \n", tsk->pid );
	len += sprintf( buf+len, "   pgd=%08lX  ", (unsigned long)mm->pgd );
	len += sprintf( buf+len, "mmap=%08lX  ", (unsigned long)mm->mmap );
	len += sprintf( buf+len, "map_count=%d  ", mm->map_count );
	len += sprintf( buf+len, "mm_users=%d  ", mm->mm_users.counter );
	len += sprintf( buf+len, "mm_count=%d  ", mm->mm_count.counter );
	len += sprintf( buf+len, "\n" );
	len += sprintf( buf+len, "    start_code=%08lX  ", mm->start_code );
	len += sprintf( buf+len, " end_code=%08lX\n", mm->end_code );
	len += sprintf( buf+len, "    start_data=%08lX  ", mm->start_data );
	len += sprintf( buf+len, " end_data=%08lX\n", mm->end_data );
	len += sprintf( buf+len, "     start_brk=%08lX  ", mm->start_brk );
	len += sprintf( buf+len, "      brk=%08lX\n", mm->brk );
	len += sprintf( buf+len, "     arg_start=%08lX  ", mm->arg_start );
	len += sprintf( buf+len, "  arg_end=%08lX\n", mm->arg_end );
	len += sprintf( buf+len, "     env_start=%08lX  ", mm->env_start );
	len += sprintf( buf+len, "  env_end=%08lX\n", mm->env_end );
	len += sprintf( buf+len, "   start_stack=%08lX  ", mm->start_stack );
	len += sprintf( buf+len, "end_stack=%08lX\n", TASK_SIZE );
	len += sprintf( buf+len, "\n" );
	return	len;
}

int init_module( void )
{
	printk("MM Module Insereted");
	 /* set up a proc dir-entry in /proc */
	mm_info = create_proc_entry( "mm", 0, NULL );
	
	/* assign the read method of /proc/mm to dump the information */
        mm_info->read_proc = my_get_info;
      //  mm_info->owner = THIS_MODULE;

	return	0;  // SUCCESS
}

void cleanup_module( void )
{
	remove_proc_entry( "mm", NULL );
}

MODULE_LICENSE("GPL");

