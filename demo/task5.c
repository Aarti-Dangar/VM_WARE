//Find out location of  symbol LINUX_VERSION_CODE  in kernel source which represents the code for current kernel version. For a kernel version a.b.c , this code is calculated as: a * (2ˆ16) + b * (2ˆ8) + c . Implement LKM to calculate and print the kernel version, by using and decoding this code. Find the location of min3 and max3 macros in Linux kernel source. Implement LKM that prints the minimum and maximum value among three signed integers taken in from command line.
//
#include <linux/init.h>
#include<linux/printk.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include<linux/minmax.h>
#include<linux/moduleparam.h>
#include<linux/version.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple LKM to calculate and print the kernel version");
static int a=1;
static int b=2;
static int c=3;

module_param(a,int,S_IRUSR |S_IWUSR|S_IRGRP |S_IWGRP);
MODULE_PARM_DESC(a," integer value");
module_param(b,int,S_IRUSR |S_IWUSR|S_IRGRP |S_IWGRP);
MODULE_PARM_DESC(b," integer value");
module_param(c,int,S_IRUSR |S_IWUSR|S_IRGRP |S_IWGRP);
MODULE_PARM_DESC(c," integer value");

static int __init start(void)
{
	int value=LINUX_VERSION_CODE;
 pr_info("Version:%d.%d.%d\n",value>>16,(value%(1<<16))>>8,(value%(1<<16))%(1<<8));
 pr_info("integer val:%d\n",value);
 pr_info("min value of kernel version:%d\n",min3(a,b,c));
 pr_info("max value of kernel version:%d\n",max3(a,b,c));
 return 0;
}

static void __exit stop(void) 
{
    pr_info("Goodbye from the LKM\n");
}

module_init(start);
module_exit(stop);

