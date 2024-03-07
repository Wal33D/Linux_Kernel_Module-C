#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

#define DRIVER_AUTHOR "Wal33D"
#define DRIVER_DESC "Enhanced LinuxKernelModule-A5"
#define DRIVER_LICE "GPL"

static int num_birthdays = 5;
module_param(num_birthdays, int, S_IRUGO); // Allow parameter at load time
MODULE_PARM_DESC(num_birthdays, "Number of birthday structures");

typedef struct _birthday {
    int day;
    int month;
    int year;
    struct list_head list;
} birthday;

LIST_HEAD(birthday_list);

static int __init birthdayList_init(void) {
    printk(KERN_INFO "Loading Enhanced Module\n");
    
    if (num_birthdays <= 0) {
        printk(KERN_WARNING "Invalid number of birthdays: %d\n", num_birthdays);
        return -EINVAL;
    }

    birthday *person;
    for(int i = 0; i < num_birthdays; i++) {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        if (!person) {
            printk(KERN_ERR "Memory allocation for birthday failed\n");
            return -ENOMEM;
        }

        person->day = 2 + i;
        person->month = 7 + i;
        person->year = 1995 + i;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
        printk(KERN_INFO "Added: Month %d Day %d Year %d\n", person->month, person->day, person->year);
    }
    return 0;
}

static void __exit birthdayList_exit(void) {
    printk(KERN_INFO "Removing Enhanced Module\n");
    birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        printk(KERN_INFO "Removing: Month %d Day %d Year %d\n", ptr->month, ptr->day, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(birthdayList_init);
module_exit(birthdayList_exit);

MODULE_LICENSE(DRIVER_LICE);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
