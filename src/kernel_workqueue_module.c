/*
 * Kernel Workqueue Demo Module
 * Author: Wal33D
 * License: GPL
 *
 * This module illustrates the use of kernel workqueues to manage deferred tasks.
 * It initializes a workqueue and schedules a work item that periodically logs a
 * message to the kernel log. The requeue interval can be set at load time using
 * the `work_interval` parameter. Workqueues are useful for offloading tasks that should
 * not run in the interrupt context, demonstrating an important asynchronous execution
 * mechanism in the Linux kernel.
 *
 * Usage:
 *  sudo insmod kernel_workqueue_module.ko   // To insert the module
 *  dmesg                                    // To view the kernel log messages
 *  sudo rmmod kernel_workqueue_module       // To remove the module
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/slab.h> // For kmalloc and kfree

#define DRIVER_AUTHOR "Wal33D"
#define DRIVER_DESC "Kernel Workqueue Demo Module"

static unsigned int work_interval = 5; // Interval in seconds
module_param(work_interval, uint, 0644);
MODULE_PARM_DESC(work_interval, "Work item requeue interval in seconds");

static struct workqueue_struct *example_wq;
static struct delayed_work *example_work;

static void example_work_func(struct work_struct *work)
{
    (void)work; // Unused parameter
    printk(KERN_INFO "Workqueue function is executed!\n");
    // Reschedule the work after the specified interval
    if (example_wq)
        queue_delayed_work(example_wq, example_work, work_interval * HZ);
}

static int __init workqueue_demo_init(void)
{
    printk(KERN_INFO "Loading Workqueue Demo Module\n");

    // Create a workqueue
    example_wq = alloc_workqueue("example_wq", WQ_UNBOUND, 0);
    if (!example_wq)
        return -ENOMEM;

    // Allocate work
    example_work = kmalloc(sizeof(struct delayed_work), GFP_KERNEL);
    if (!example_work) {
        destroy_workqueue(example_wq);
        return -ENOMEM;
    }

    // Initialize and enqueue work
    INIT_DELAYED_WORK(example_work, example_work_func);
    queue_delayed_work(example_wq, example_work, work_interval * HZ);

    return 0;
}

static void __exit workqueue_demo_exit(void)
{
    printk(KERN_INFO "Removing Workqueue Demo Module\n");

    // Cancel and flush work
    if (example_work) {
        cancel_delayed_work_sync(example_work);
        kfree(example_work);
    }

    // Destroy the workqueue
    if (example_wq)
        destroy_workqueue(example_wq);
}

// Register module entry and exit points
module_init(workqueue_demo_init);
module_exit(workqueue_demo_exit);

// Set module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
