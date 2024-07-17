//Implement LKM which prints output in terminal instead of dmesg or kernel log.
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/tty.h>
#include <linux/sched.h>
 
MODULE_LICENSE("mit");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("Linked list module");
 
static void print_string(char *str)
{
	struct tty_struct *my_tty;
	struct tty_driver *driver;
	int written;
#if(LINUX_VERSION_CODE<=KERNEL_VERSION(2,6,5))
	my_tty=current->signal->tty;
#endif
	if(my_tty!=NULL){
		driver=my_tty->driver;
		written=driver->ops->write(my_tty,str,strlen(str));
		if(written<0){
			pr_err("Failed to write to tty\n");
		}
		written=driver->ops->write(my_tty,"\015\012",2);
		if(written<0){
			pr_err("Failed to written newline to tty\n");
		}
	}
	else {
		pr_err("No tty found for current task\n");
	}
}
static int __init start_fun(void)
{
	print_string("Hello World! \n");
	return 0;
}
 
static void __exit stop_fun(void)
{
	print_string("Thank you, Bye\n");
}
 
module_init(start_fun);
module_exit(stop_fun);

