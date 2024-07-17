//task_10:Load the module you wrote in Exercise 2 . Then implement LKM which accepts the name of that kernel module as command-line argument and traverse the list of loaded kernel modules to find it. When you find it, print its name as well as call its "init" function!
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/kmod.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("LKM to find and print info about a specified module");

static char *target_module_name = "";
module_param(target_module_name, charp, 0644);
MODULE_PARM_DESC(target_module_name, "The name of the target kernel module");

static int __init find_module_init(void)
{
    struct module *mod;
    int found = 0;
    if(strcmp(target_module_name," ")==0)
    {
	printk(KERN_ERR "module name not given\n");
	    return -1;
    }
    pr_info("find_module: Looking for module named %s\n", target_module_name);

    list_for_each_entry(mod, THIS_MODULE->list.prev, list) {
        if (strcmp(mod->name, target_module_name) == 0) {
            found = 1;
            pr_info("find_module: Found module %s\n", mod->name);
            break;
        }
    }
if (!found) {
        pr_info("find_module: Module %s not found\n", target_module_name);
    }

    return 0;

}

static void __exit find_module_exit(void)
{
    pr_info("find_module: Module unloaded\n");
}

module_init(find_module_init);
module_exit(find_module_exit);

