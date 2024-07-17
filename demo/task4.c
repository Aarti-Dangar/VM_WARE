//task_4:Implement LKM  to crash the kernel in the easiest.  Verify by looking at the kernel logs for a kernel oops message. Then reboot.
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/utsname.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple LKM to crash the kernel in the easiest");

static int __init start(void)
{
//int a=10,b=0,c;
//c=a/b;
int *ptr=NULL;
*ptr=10;
pr_info("your kernel is crash\n");
return 0;
}

static void __exit stop(void) {
    pr_info("Goodbye from the LKM\n");
}

module_init(start);
module_exit(stop);


