//task_2 Implement LKM  to print hostname  and email ID in the kernel logs. Name your init and cleanup functions as "start" and "stop", respectively, instead of init_module and cleanup_module .
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/utsname.h> // for utsname structure

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple LKM to print hostname and email ID");

// Initialization function
static int __init start(void) {
    struct new_utsname *uts;
    uts = utsname(); // Get the system's utsname structure
    pr_info( "Hostname: %s\n", uts->nodename);
    pr_info("Email: aarti.danagr@einfochips.com\n");
    return 0;
}

// Cleanup function
static void __exit stop(void) {
   pr_info( "Goodbye from the LKM\n");
}

module_init(start);
module_exit(stop);

