/*
This module creates a pseudo-file named '/proc/pageinfo' to
show the sizes of various data-types used in the definition 
for the kernel's 'struct page' object, and the total length 
of a 'struct page' object for our kernel's configuration.

NOTE: Developed and tested with Linux kernel version 2.6.10
Author:Team veda
written on: 02 FEB 2005
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
#include <linux/proc_fs.h>	// for create_proc_info_entry() 
#include <linux/mm.h>		// for 'struct page' definition

/* /proc/pageinfo "file-descriptor" */
struct proc_dir_entry *page_info;

static char modname[] = "pageinfo";

static int my_get_info( char *buf, char **start, off_t off, int count )
{
	int	flsz = sizeof( unsigned long );
	int	atsz = sizeof( atomic_t );
	int	pvsz = sizeof( unsigned long );
	int	assz = sizeof( struct address_space * );
	int	posz = sizeof( pgoff_t );
	int	lhsz = sizeof( struct list_head );
	int	pgsz = sizeof( struct page );
	int	len = 0;
	
	printk("in read callback");

	len += sprintf( buf+len, "\nsizeof( flags ) = %d bytes ", flsz );
	len += sprintf( buf+len, "\nsizeof( atomic_t ) = %d bytes ", atsz );
	len += sprintf( buf+len, "\nsizeof( unsigned long ) = %d bytes", pvsz );
	len += sprintf( buf+len, "\nsizeof( struct address_space * ) " );
	len += sprintf( buf+len, "= %d bytes ", assz );
	len += sprintf( buf+len, "\nsizeof( pgoff_t ) = %d bytes ", posz );
	len += sprintf( buf+len, "\nsizeof( pgoff_t ) = %d bytes ", posz );
	len += sprintf( buf+len, "\nsizeof( struct list_head ) = " );
	len += sprintf( buf+len, "%d bytes  ", lhsz );
	len += sprintf( buf+len, "\nsizeof( struct page ) = %d bytes ", pgsz );
	len += sprintf( buf+len, "\n\n" );
	return	len;
}

int init_module( void )
{
	printk( "<1>\nInstalling \'%s\' module\n", modname );
	/* set up a proc dir-entry in /proc */
	page_info = create_proc_entry( modname, 0, NULL );

	/* assign the read method of /proc/pageinfo to dump the information */
        page_info->read_proc = (read_proc_t *)my_get_info;
//        page_info->owner = THIS_MODULE;

	return	0;  //SUCCESS
}

void cleanup_module( void )
{
	remove_proc_entry( modname, NULL );
	printk( "<1>Removing \'%s\' module\n", modname );
}

MODULE_LICENSE("GPL");
