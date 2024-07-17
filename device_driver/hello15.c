#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
MODULE_LICENSE("GPL");
static int test_hello_init(void)
{
dev_t devicenumber;
char buffer[20];
devicenumber=MKDEV(120,30);

printk("Devicenumber Number :%s\n",format_dev_t(buffer,devicenumber));
buffer[0]='\0';
printk("print_dev_t returned  :%d device number:%s\n",print_dev_t(buffer,devicenumber),buffer);
return 0;
}
static void test_hello_exit(void)
{

}
module_init(test_hello_init);
module_exit(test_hello_exit);
