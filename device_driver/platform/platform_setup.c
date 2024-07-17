#include<linux/module.h>
#include<linux/platform_device.h>
 
#include "platform.h"
 
#undef pr_fmt
#define pr_fmt(fmt) "%s : " fmt,__func__
 
void pcdev_release(struct device *dev)
{
	pr_info("Device released \n");
}
 
 
/*1. create  platform data */
struct pcdev_platform_data  pcdev_pdata[] = {
	[0] = {.size = 512, .perm = RDWR,   .serial_number = "PCDEVABC1111"},
};
 
/*2. create  platform device */
 
struct platform_device platform_pcdev_1 = {
	.name = "pcdev-A1x",
	.id = 0,
	.dev = {
		.platform_data = &pcdev_pdata[0],
		.release = pcdev_release
	}
};
 
struct platform_device *platform_pcdevs[] = 
{
&platform_pcdev_1,
};
 
static int __init pcdev_platform_init(void)
{
	/* register n platform devices */
 
        platform_device_register(&platform_pcdev_1);
	platform_add_devices(platform_pcdevs,ARRAY_SIZE(platform_pcdevs) );
 
	pr_info("Device setup module loaded \n");
 
	return 0;
}
 
 
static void __exit pcdev_platform_exit(void)
{
 
	platform_device_unregister(&platform_pcdev_1);
	pr_info("Device setup module unloaded \n");
 
 
}
 
module_init(pcdev_platform_init);
module_exit(pcdev_platform_exit);
 
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(" Platform device setup - demo ");
MODULE_AUTHOR("CCL");
