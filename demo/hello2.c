#include<linux/module.h>
#include<linux/init.h>//need for module
#include<linux/printk.h>
int init_module(void)
{
	pr_info("hello world 1.\n");
	return 0;
}
void cleanup_module(void)
{
	pr_info("Goodbye world 1.\n");

}
module_init(hello2_init);
module_exit(hello2.exit);
MODULE_LICENSE("GPL");
