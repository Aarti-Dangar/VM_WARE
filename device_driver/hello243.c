//llseek function implementation 

#include <linux/kernel.h>	
#include <linux/module.h>	
#include <linux/kdev_t.h>	
#include <linux/printk.h>	
#include <linux/cdev.h>	
#include <linux/device.h>	
#include <linux/delay.h>	
#include <linux/fs.h>	
#include <linux/uaccess.h>	

int base_minor=0;
char *device_name = "msg243";
int count=1;
dev_t  dev_num;

static struct class *class=NULL;
static struct device *device=NULL;
static struct cdev mycdev;

#define MAX_SIZE 1024
char kernel_buffer[MAX_SIZE];
int buffer_index;
MODULE_LICENSE("GPL");

static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n",__func__);
	file->f_pos = 0;
	buffer_index = 0;
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n",__func__);
	return 0;
}

static ssize_t device_read(struct file *file ,char __user *user_buffer,size_t read_count,loff_t *offset)
{
	int bytes_read;
	int available_space;
	int bytes_to_read;
	
	pr_info("%s read offset:%lld\n",__func__, *offset);
	available_space = MAX_SIZE - *(offset);
	
	if(read_count < available_space)
		bytes_to_read = read_count;
	else
		bytes_to_read = available_space;
	if(bytes_to_read == 0) {
		pr_err("%s: No available spcae in the buffer for readinf\n",__func__);
		return -ENOSPC;
	}

	if( buffer_index > *offset )
		bytes_to_read = buffer_index - *offset;
	else
		return 0;
	
	bytes_read = bytes_to_read - copy_to_user(user_buffer,kernel_buffer+*offset, bytes_to_read);
	pr_info("%s: copy to user returned:%d\n",__func__,bytes_to_read);
	
	//update file offset
	*offset  += bytes_read;
	
	return bytes_read;
}

static ssize_t device_write(struct file *file ,const char __user *user_buffer,size_t write_count,loff_t *offset)
{
	int bytes_written;
        int available_space;
        int bytes_to_write;

        pr_info("%s write offset:%lld\n",__func__, *offset);
        available_space = MAX_SIZE - *(offset);

        if(write_count < available_space)
                bytes_to_write = write_count;
        else
                bytes_to_write = available_space;
        if(bytes_to_write == 0) {
                pr_err("%s: No available spcae in the buffer for writing\n",__func__);
                return 0;
        }
        else
                return 0;

        bytes_written = bytes_to_write - copy_from_user( kernel_buffer+(*offset), user_buffer, bytes_to_write);
        pr_info("%s: Bytes written:%d\n",__func__,bytes_written);
        pr_info("%s: Kernel buffer:%s\n",__func__,kernel_buffer);

        //update file offset
        *offset  += bytes_written;
	buffer_index += bytes_written;
	
        return bytes_written;
}

struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
};

static int test_hello5_init(void)
{
	class=class_create(THIS_MODULE,"myclass6a");
	if(!alloc_chrdev_region(&dev_num,base_minor,count,device_name)){
		printk("Device number registerd\n");
		printk("Major number received:%d\n",MAJOR(dev_num));
		device=device_create(class,NULL,dev_num,NULL,device_name);
		cdev_init(&mycdev,&device_fops);
		mycdev.owner = THIS_MODULE;
		cdev_add(&mycdev,dev_num,count);
	}
	else
		printk("Device number not regestered\n");
	return 0;
}

static void test_exit(void)
{
	unregister_chrdev_region(dev_num,count);
	cdev_del(&mycdev);
	device_destroy(class,dev_num);
	class_destroy(class);
	printk("Driver unloaded\n");
}

module_init(test_hello5_init);
module_exit(test_exit);
