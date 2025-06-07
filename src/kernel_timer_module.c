/*
 * Kernel Timer Demo Module
 * Author: Wal33D
 * License: MIT
 *
 * This module demonstrates the use of kernel timers to execute tasks periodically.
 * A kernel timer is initialized to trigger a callback function periodically.
 * The interval can be set when the module is loaded using the `timer_interval`
 * parameter. Each expiry logs a message to the kernel log. This example showcases the mechanism for
 * scheduling and handling timed events within the Linux kernel.
 *
 * Usage:
 *  sudo insmod kernel_timer_module.ko   // To insert the module
 *  dmesg                                // To view the kernel log messages
 *  sudo rmmod kernel_timer_module       // To remove the module
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

#define DRIVER_AUTHOR "Wal33D"
#define DRIVER_DESC "Kernel Timer Demo Module"

static unsigned int timer_interval = 5; // Interval in seconds
module_param(timer_interval, uint, 0644);
MODULE_PARM_DESC(timer_interval, "Timer interval in seconds");

static struct timer_list my_timer;

// Function to be called when the timer expires
static void timer_callback(struct timer_list *timer)
{
    printk(KERN_INFO "Timer expired and callback function is called!\n");
    
    // Reschedule the timer for another timer_interval seconds later
    mod_timer(timer, jiffies + timer_interval * HZ);
}

static int __init timer_demo_init(void)
{
    printk(KERN_INFO "Loading Timer Demo Module\n");
    
    // Timer setup
    timer_setup(&my_timer, timer_callback, 0);
    
    // Schedule the timer for the first time
    mod_timer(&my_timer, jiffies + timer_interval * HZ);
    
    return 0; // Module successfully loaded
}

static void __exit timer_demo_exit(void)
{
    printk(KERN_INFO "Removing Timer Demo Module\n");
    
    // Delete the timer
    del_timer_sync(&my_timer);
}

// Register module entry and exit points
module_init(timer_demo_init);
module_exit(timer_demo_exit);

// Set module metadata
MODULE_LICENSE("MIT");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
