/*
This module creates a pseudo-file (named '/proc/vma') which
allows a user-task to see information about its memory-map.
(The various Virtual Memory Areas which are associated with 
a task are maintained by the kernel within a linked-list of
'vm_area_struct' objects in the task's 'mm_struct' object.)

NOTE: Developed and tested with Linux kernel version 2.6.10.

AUTHOR:Team Veda
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
#include <linux/mm.h>		// for 'struct vm_area_struct'
#include <linux/sched.h>

/* /proc/vma "file-descriptor" */
struct proc_dir_entry *vma_info;

char modname[] = "vma";

int my_get_info( char *buf, char **start, off_t off, int count )
{
	struct task_struct	*tsk = current;
	struct vm_area_struct	*vma;
	unsigned long 		ptdb;
	int			i = 0, len = 0;
	
	// display title
	len += sprintf( buf+len, "\n\nList of the Virtual Memory Areas " );
	len += sprintf( buf+len, "for task \'%s\' ", tsk->comm );
	len += sprintf( buf+len, "(pid=%d)\n", tsk->pid );

	// loop to traverse the list of the task's vm_area_structs
	vma = tsk->mm->mmap;
	while ( vma )
		{
		char	ch;	
		len += sprintf( buf+len, "\n%3d ", ++i );
		len += sprintf( buf+len, " vm_start=%08lX ", vma->vm_start );
		len += sprintf( buf+len, " vm_end=%08lX  ", vma->vm_end );

		ch = ( vma->vm_flags & VM_READ ) ? 'r' : '-';
		len += sprintf( buf+len, "%c", ch );
		
		ch = ( vma->vm_flags & VM_WRITE ) ? 'w' : '-';
		len += sprintf( buf+len, "%c", ch );
		
		ch = ( vma->vm_flags & VM_EXEC ) ? 'x' : '-';
		len += sprintf( buf+len, "%c", ch );

		ch = ( vma->vm_flags & VM_SHARED ) ? 's' : 'p';
		len += sprintf( buf+len, "%c", ch );
		
		vma = vma->vm_next;
		}
	len += sprintf( buf+len, "\n" );

	// display additional information about tsk->mm
	asm(" movl %%cr3, %%ecx \n movl %%ecx, %0 " : "=m" (ptdb) );
	len += sprintf( buf+len, "\nCR3=%08lX ", ptdb );
	len += sprintf( buf+len, " mm->pgd=%p ", tsk->mm->pgd );
	len += sprintf( buf+len, " mm->map_count=%d ", tsk->mm->map_count );
	len += sprintf( buf+len, "\n\n" );

	return	len;
}

int init_module( void )
{
	printk( "<1>\nInstalling \'%s\' module\n", modname );
	/* set up a proc dir-entry in /proc */
	vma_info = create_proc_entry( modname, 0, NULL );
	
	/* assign the read method of /proc/vma to dump the information */
        vma_info->read_proc = my_get_info;
       // vma_info->owner = THIS_MODULE;

	return	0; // SUCCESS
}


void cleanup_module( void )
{
	remove_proc_entry( modname, NULL );
	printk( "<1>Removing \'%s\' module\n", modname );
}

MODULE_LICENSE("GPL"); 

