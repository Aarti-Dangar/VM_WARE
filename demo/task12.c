//Implement LKM which acts as modinfo command.
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple module that acts like the modinfo command.");
MODULE_VERSION("1.0");

static int __init start(void) {
    printk(KERN_INFO "Module Info: Loading the modinfo-like module\n");
    printk(KERN_INFO "Author: %s\n", MODULE_AUTHOR);
    printk(KERN_INFO "Description: %s\n", MODULE_DESCRIPTION);
    printk(KERN_INFO "License: %s\n", MODULE_LICENSE);
    printk(KERN_INFO "Version: %s\n", MODULE_VERSION);
    return 0;
}

static void __exit stop(void) {
    printk(KERN_INFO "Module Info: Unloading the modinfo-like module\n");
}

module_init(start);
module_exit(stop);

