#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include<linux/export.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aaarti");
MODULE_DESCRIPTION("A another module to access an exported variable.");

extern int my_var;

static int __init start(void)
{
    pr_info("another module loaded. my_var = %d\n", my_var);
    return 0;
}

static void __exit stop(void)
{
    pr_info("another module unloaded\n");
}

module_init(start);
module_exit(stop);

