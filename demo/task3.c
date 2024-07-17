//task_3:Implement LKM  to try out various kernel logging levels using printk . Print a string to the "terminal" using one of the kernel log levels. Also find out all the log levels that print to the terminal by default.
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/utsname.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple LKM to demonstrate kernel logging levels");

static int __init start(void) {
    struct new_utsname *uts;
    uts = utsname(); // Get the system's utsname structure

    // Demonstrating various log levels
    printk(KERN_EMERG "KERN_EMERG: System is unusable\n");
    printk(KERN_ALERT "KERN_ALERT: Action must be taken immediately\n");
    printk(KERN_CRIT "KERN_CRIT: Critical conditions\n");
    printk(KERN_ERR "KERN_ERR: Error conditions\n");
    printk(KERN_WARNING "KERN_WARNING: Warning conditions\n");
    printk(KERN_NOTICE "KERN_NOTICE: Normal but significant condition\n");
    printk(KERN_INFO "KERN_INFO: Informational\n");
    printk(KERN_DEBUG "KERN_DEBUG: Debug-level messages\n");

    // Print hostname and email at a level that typically shows up on the terminal
    printk(KERN_NOTICE "Hostname: %s\n", uts->nodename);
    printk(KERN_NOTICE "Email: aarti.dangar@einfochips.com\n");

    return 0;
}

static void __exit stop(void) {
    printk(KERN_INFO "Goodbye from the LKM\n");
}

module_init(start);
module_exit(stop);

