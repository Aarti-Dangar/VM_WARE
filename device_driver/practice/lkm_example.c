#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
 
#define DEVICE_NAME "lkm_example"
#define EXAMPLE_MSG "Hello from my_function!\n"
#define MSG_BUFFER_LEN 100
 
static int major_num;
static char msg_buffer[MSG_BUFFER_LEN] = EXAMPLE_MSG;
static char *msg_ptr;
 
void my_function(void)
{
   pr_info("Hello from my_function!\n");
}
 
EXPORT_SYMBOL(my_function);
 
static int device_open(struct inode *inode, struct file *file)
{
   msg_ptr = msg_buffer;
   return 0;
}
 
static int device_release(struct inode *inode, struct file *file)
{
   return 0;
}
 
static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
   int bytes_read = 0;
   if (*msg_ptr == 0) return 0;
 
   while (length && *msg_ptr) {
       put_user(*(msg_ptr++), buffer++);
       length--;
       bytes_read++;
   }
 
   return bytes_read;
}
 
static struct file_operations fops = {
   .read = device_read,
   .open = device_open,
   .release = device_release,
};
 
static int __init lkm_example_init(void)
{
   major_num = register_chrdev(0, DEVICE_NAME, &fops);
   if (major_num < 0) {
       printk(KERN_ALERT "Registering char device failed with %d\n", major_num);
       return major_num;
   }
   printk(KERN_INFO "lkm_example module loaded with device major number %d\n", major_num);
   return 0;
}
 
static void __exit lkm_example_exit(void)
{
   unregister_chrdev(major_num, DEVICE_NAME);
   printk(KERN_INFO "lkm_example module unloaded\n");
}
 
module_init(lkm_example_init);
module_exit(lkm_example_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple LKM example with a device file");
 
