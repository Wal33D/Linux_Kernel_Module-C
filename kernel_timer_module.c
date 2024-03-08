/*
 * Kernel Timer Demo Module
 * Author: Wal33D
 * License: GPL
 *
 * This module demonstrates the use of kernel timers to perform periodic tasks.
 * It sets up a timer that logs a message to the kernel log every 5 seconds.
 *
 * Usage:
 *  sudo insmod kernel_timer_module.ko   // To insert the module
 *  dmesg                              // To view the kernel log messages
 *  sudo rmmod kernel_timer_module       // To remove the module
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

#define DRIVER_AUTHOR "Wal33D"
#define DRIVER_DESC "Kernel Timer Demo Module"
#define TIMER_INTERVAL HZ*5 // 5 seconds; HZ is number of ticks per second

static struct timer_list my_timer;

// Function to be called when the timer expires
static void timer_callback(struct timer_list *timer)
{
    printk(KERN_INFO "Timer expired and callback function is called!\n");
    
    // Reschedule the timer for another TIMER_INTERVAL seconds later
    mod_timer(timer, jiffies + TIMER_INTERVAL);
}

static int __init timer_demo_init(void)
{
    printk(KERN_INFO "Loading Timer Demo Module\n");
    
    // Timer setup
    timer_setup(&my_timer, timer_callback, 0);
    
    // Schedule the timer for the first time
    mod_timer(&my_timer, jiffies + TIMER_INTERVAL);
    
    return 0; // Module successfully loaded
}

static void __exit timer_demo_exit(void)
{
    printk(KERN_INFO "Removing Timer Demo Module\n");
    
    // Delete the timer
    del_timer(&my_timer);
}

// Register module entry and exit points
module_init(timer_demo_init);
module_exit(timer_demo_exit);

// Set module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
