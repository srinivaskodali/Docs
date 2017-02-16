/*
 * Author:Team veda
 * Developed and tested with: Linux kernel version 2.6.10
 * Tested with: Linux kernel version 2.6.29 also
 *
 * Code changes after 2.6.29 kernel version:
 * 1) In #include <linux/workqueue.h>,
 *            DECLARE_WORK() is taking 2 arguments instead of 3.
 */


#ifndef __KERNEL__
 #define __KERNEL__
#endif

#ifndef MODULE
 #define MODULE
#endif


/* Demonstration of WORK-QUEUES*/
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/workqueue.h>
#include <linux/sched.h>

#define DELAY	100
int wq_init(void);
void wq_exit(void);
void wq_func(void *);


MODULE_LICENSE("GPL");
module_init(wq_init);
module_exit(wq_exit);

static int counter;

DECLARE_WORK(wq,(work_func_t)wq_func);
//create_workqueue(myqueue);

void wq_func(void *arg)
{
	printk("%ld %d %s \n", jiffies,counter++,current->comm);
        if( counter < 1000 )
                schedule_work(&wq);
}

int  wq_init(void)
{
	printk("\nModule Inserted\n");
	//INIT_WORK(wq,wq_func,0);
	schedule_work(&wq);
		
	
	printk("current counter %ld\n",jiffies);
//	schedule_delayed_work(&wq,DELAY);
	printk("current counter %ld\n",jiffies);
	return 0;	
}

void wq_exit()
{
printk("\nModule Removed");
}

/* Browse linux/workqueue.h for further symbols.*/
