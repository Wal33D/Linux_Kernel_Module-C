/*
 * Birthday List Linux Kernel Module
 * Author: Wal33D
 * License: MIT
 *
 * This module demonstrates creating a linked list in kernel space.
 * It allows setting the number of birthday records to create via module parameter 'num_birthdays'
 * at load time. Each record represents a person's birthday. The module prints these birthdays
 * to the kernel log when loaded and also upon removal, cleans up the memory allocated for the
 * birthday records.
 *
 * Usage:
 *  sudo insmod kernel_birthday_list_module.ko num_birthdays=5  // To insert module and specify number of birthdays
 *  dmesg  // To view the kernel log messages
 *  sudo rmmod kernel_birthday_list_module  // To remove the module
 */

#include <linux/module.h>   // Essential for all modules
#include <linux/kernel.h>   // For KERN_INFO, KERN_WARNING, and KERN_ERR
#include <linux/init.h>     // For __init and __exit macros
#include <linux/list.h>     // For linked list operations
#include <linux/types.h>    // For data type definitions
#include <linux/slab.h>     // For memory allocation functions

#define DRIVER_AUTHOR "Wal33D"
#define DRIVER_DESC   "Enhanced Birthday List Linux Kernel Module"
#define DRIVER_LICENSE "MIT"
static int num_birthdays = 5; // Default number of birthdays to generate

// Allows setting of num_birthdays at module load time, visible with S_IRUGO permission
module_param(num_birthdays, int, S_IRUGO);

// Defines a structure to hold a birthday
typedef struct _birthday {
    int day;            // Day of the birthday
    int month;          // Month of the birthday
    int year;           // Year of the birthday
    struct list_head list; // Kernel's list structure to link these structures
} birthday;

// Initializes the head of the linked list
LIST_HEAD(birthday_list);

// Module load function marked with __init to free memory after initialization
static int __init birthdayList_init(void) {
    printk(KERN_INFO "Loading Enhanced Module\n");
    
    // Validate the number of birthdays
    if (num_birthdays <= 0) {
        printk(KERN_WARNING "Invalid number of birthdays: %d\n", num_birthdays);
        return -EINVAL; // Return with invalid argument error code
    }

    // Allocate and initialize the specified number of birthday structures
    for(int i = 0; i < num_birthdays; i++) {
        birthday *person = kmalloc(sizeof(*person), GFP_KERNEL); // Allocate memory
        if (!person) {
            printk(KERN_ERR "Memory allocation for birthday failed\n");
            birthday *cur, *tmp;
            list_for_each_entry_safe(cur, tmp, &birthday_list, list) {
                list_del(&cur->list);
                kfree(cur);
            }
            return -ENOMEM; // Return with out of memory error code
        }

        // Assign values to the new person's birthday
        person->day = 2 + i;
        person->month = 7 + i;
        person->year = 1995 + i;
        INIT_LIST_HEAD(&person->list); // Initialize the list head
        list_add_tail(&person->list, &birthday_list); // Add to the end of the list
        printk(KERN_INFO "Added: Month %d Day %d Year %d\n", person->month, person->day, person->year);
    }
    return 0; // Indicates successful module initialization
}

// Module unload function marked with __exit to indicate it's not needed after module unload
static void __exit birthdayList_exit(void) {
    printk(KERN_INFO "Removing Enhanced Module\n");
    birthday *ptr, *next;
    
    // Traverse the list and free allocated memory
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        printk(KERN_INFO "Removing: Month %d Day %d Year %d\n", ptr->month, ptr->day, ptr->year);
        list_del(&ptr->list); // Remove from list
        kfree(ptr); // Free memory allocated for the birthday
    }
}

// Register module entry and exit points
module_init(birthdayList_init);
module_exit(birthdayList_exit);

// Set module metadata
MODULE_LICENSE(DRIVER_LICENSE);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
