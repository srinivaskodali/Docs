/*
 * First module program
 * Author:Team-c
 * Version:1.0
 * Tested with: Linux kernel version 2.6.29 also
 *
 * Code changes after 2.6.29 kernel version:
 *     1) The variable kmem_cache_t (used in fuctions to allocate cache memory in
 *        #include<linux/slab.h>) is changed to struct kmem_cache (defined in #include<linux/slub_def.h>)
 *     2) kmem_cache_create() is taking 5 arguments instead of 6.
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
#include<linux/slab.h>
#include<linux/mempool.h>


#define SUCCESS 0
mempool_t *mem;
struct kmem_cache *cache_ptr;
int *ret;
typedef struct abc{
	int a;
	int b;
	int c;
}abc_t;
abc_t *ptr;
int var=12;
void func(void);

void func(void)
{
//ret=kmem_cache_alloc(cache_ptr,GFP_KERNEL);
ptr=(struct abc *)mempool_alloc(mem,GFP_KERNEL);
ptr->a=100;
ptr->b=300;
ptr->c=700;
printk("val is %d",ptr->a);
}
int init_mod(void)
{
cache_ptr=kmem_cache_create("cache_mem1",var,0,SLAB_HWCACHE_ALIGN,NULL);
mem=mempool_create(20,mempool_alloc_slab,mempool_free_slab,cache_ptr);

if(mem==NULL)
	return -ENOMEM;

printk("\nModule loaded");
func();
return SUCCESS;
}

void cleanup_mod(void)
{
printk("\n Module removed");

mempool_free(ptr,mem);
mempool_destroy(mem);
//kmem_cache_free(cache_ptr,ret);
kmem_cache_destroy(cache_ptr);
//mempool_free(ptr,mem);

}

module_init(init_mod);
module_exit(cleanup_mod);

/*Kernel module Comments*/
MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("FIRST MODULE");
MODULE_LICENSE("GPL");
