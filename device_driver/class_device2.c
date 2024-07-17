#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/delay.h>
#include<linux/device.h>
#include <linux/cdev.h>
#include<linux/printk.h>
#include<linux/fs.h>
MODULE_LICENSE("GPL");

int base_minor=0;
char *device_name="mychardev5";
int count=1;
dev_t devicenumber;


static struct class *class;
static struct device *device;
static int test_hello_init(void)
{

	class = class_create(THIS_MODULE,"myclass5");
	if(!alloc_chrdev_region(&devicenumber,base_minor,count,device_name))
	{
		printk("DEvice number registered\n");
		printk("Major number received:%d\n",MAJOR(devicenumber));
	device = device_create(class,NULL,devicenumber,NULL,device_name);
	}
	else
printk("device number registration failed\n");
return 0;
}
static void test_hello_exit(void)
{
	unregister_chrdev_region(devicenumber,count);
	device_destroy(class,devicenumber);
	class_destroy(class);
printk("Device Destroyed\n");
}
module_init(test_hello_init);
module_exit(test_hello_exit);
