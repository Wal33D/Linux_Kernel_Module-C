/*  
 *  hello-3.c - Illustrating the __init, __initdata and __exit macros.
 *  
 *
 */

#include <linux/module.h>   /* Needed by all modules  */
#include <linux/kernel.h>   /* Needed for KERN_INFO   */
#include <linux/init.h>     /* Needed for the macros  */
#include <linux/list.h>     /* Needed for linked list */
#include <linux/types.h>    /* Needed for list macros */
#include <linux/slab.h>     /* Needed for Kernel */

#define DRIVER_AUTHOR       "Waleed Gudah"
#define DRIVER_DESC         "LinuxKernelModule-A5"
#define DRIVER_LICE         "GPL"
#define NUM_OF_BIRTHDAYS    6

/* Example struct we will use. */
typedef struct _birthday {
    
    int day;
    int month;
    int year;
    struct list_head list;

}birthday;

/* Declare and init the head of the linked list. */
LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int birthdayList_init(void) {

    printk(KERN_INFO "Loading Module\n");

    /* Allocate 5 birthdays from kernel */
    birthday *person;
    int i = 0;
    for(i = 0; i < NUM_OF_BIRTHDAYS; i++) {
        /* Request malloc to the kernel. */
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        /* Assign value to the struct. */
        person->day = 2 + i;
        person->month = 7 + i;
        person->year = 1995 + i;
        /* Init the list within the struct. */
        INIT_LIST_HEAD(&person->list);
        /* Add this struct to the tail of the list. */
        list_add_tail(&person->list, &birthday_list);

    }

    /* Go thru the list and print. */
    birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) {

        printk(KERN_INFO "Birthday: Month %d Day %d Year %d\n",
                ptr->month,
                ptr->day,
                ptr->year);
    }

           return 0;
}

/* This function is called when the module is removed. */
void birthdayList_exit(void) {

    printk(KERN_INFO "Removing Module\n");

    /* Go thru the list and free the memory. */
    birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {

        printk(KERN_INFO "Removing Birthday: Month %d Day %d Year %d\n",
                ptr->month,
                ptr->day,
                ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }

    printk(KERN_INFO "Memory free done\n");
}

/* Macros for registering module entry and exit points. */
module_init(birthdayList_init);
module_exit(birthdayList_exit);

MODULE_LICENSE(DRIVER_LICE);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);