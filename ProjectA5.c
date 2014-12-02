#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
/* This function is called when the module is loaded. */
int simple_init(void)
{
printk(KERN INFO "Removing Module\n");
}
/* Macros for registering module entry and exit points. */
module init(simple_init);
module exit(simple_exit);

MODULE LICENSE("GPL");
MODULE DESCRIPTION("Simple Module");
MODULE AUTHOR("SGG");