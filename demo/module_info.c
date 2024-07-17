#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM to display information about a specified module");
MODULE_VERSION("1.0");

static char *target_module_name = NULL;
module_param(target_module_name, charp, 0644);
MODULE_PARM_DESC(target_module_name, "The name of the target kernel module");

static int __init modinfo_lkm_init(void)
{
    struct module *mod;
    int found = 0;

    if (!target_module_name) {
        pr_err("modinfo_lkm: No module name specified\n");
        return -EINVAL;
    }

    pr_info("modinfo_lkm: Module loaded\n");
    pr_info("modinfo_lkm: Looking for module named %s\n", target_module_name);

    // Traverse the list of loaded modules
    list_for_each_entry(mod, THIS_MODULE->list.prev, list) {
        if (strcmp(mod->name, target_module_name) == 0) {
            found = 1;
            pr_info("modinfo_lkm: Module Name: %s\n", mod->name);
            pr_info("modinfo_lkm: Version: %s\n", mod->version);
            pr_info("modinfo_lkm: Author: %s\n", mod->author);
            pr_info("modinfo_lkm: Description: %s\n", mod->init_layout);
            pr_info("modinfo_lkm: License: %s\n", mod->license);
            pr_info("modinfo_lkm: Init function address: %p\n", mod->init);
            pr_info("modinfo_lkm: Exit function address: %p\n", mod->exit);
            pr_info("modinfo_lkm: Module state: %d\n", mod->state);
            pr_info("modinfo_lkm: Number of refs: %d\n", module_refcount(mod));
            break;
        }
    }

    if (!found) {
        pr_info("modinfo_lkm: Module %s not found\n", target_module_name);
    }

    return 0;
}

static void __exit modinfo_lkm_exit(void)
{
    pr_info("modinfo_lkm: Module unloaded\n");
}

module_init(modinfo_lkm_init);
module_exit(modinfo_lkm_exit);

