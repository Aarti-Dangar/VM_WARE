//task_15:Implement LKM  to access a take a command-line argument which sets the value of a variable. Then access this variable from another kernel module. Use EXPORT_SYMBOL in the first module and access it in another module by using extern.
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include<linux/export.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A first module to export a variable.");

 int my_var = 0;
module_param(my_var, int,S_IRUSR |S_IWUSR|S_IRGRP |S_IWGRP);
MODULE_PARM_DESC(my_var, "An integer variable");

EXPORT_SYMBOL(my_var);

static int __init start(void)
{
    pr_info("first module loaded with my_var = %d\n", my_var);
    return 0;
}

static void __exit stop(void)
{
    pr_info("first  module unloaded\n");
}

module_init(start);
module_exit(stop);

