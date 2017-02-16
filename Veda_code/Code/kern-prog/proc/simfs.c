/*Module Demonstrating simple filesystem implemenatation using libfs
Author:Team-c
Version:1.0
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>



static struct file_system_type simfs={
	.owner	= THIS_MODULE,
	.name	= "simfs"
	.getsb	= simfs_get_super,
	.kill_sb= kill_litter_super,
};


static int __init simfs_init(void)
{
	return register_filesystem(&simfs);
}

static void __exit simfs_exit(void)
{
	unregister_filesystem(&simfs);
}	
