//access 

#include <linux/kernel.h>	
#include <linux/module.h>	
#include <linux/kdev_t.h>	
#include <linux/printk.h>	
#include <linux/cdev.h>	
#include <linux/device.h>	
#include <linux/delay.h>	
#include <linux/fs.h>	
#include <linux/uaccess.h>	
#include "ioctl_cmd2.h"
int base_minor=0;
char *device_name = "accessok1";
int count = 1;
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
		return -ENOSPC;
        }

        bytes_written = bytes_to_write - copy_from_user( kernel_buffer+(*offset), user_buffer, bytes_to_write);
	strcat(kernel_buffer," ");
	pr_info("%s: Bytes written:%d\n",__func__,bytes_written);
        pr_info("%s: Kernel buffer:%s\n",__func__,kernel_buffer);

        //update file offset
        *offset  += bytes_written;
	buffer_index += bytes_written;
	
        return bytes_written;
}

static loff_t device_lseek(struct file *file, loff_t offset, int orig)
{
    loff_t new_pos = 0;

    switch(orig) {
        case 0: /* seek set */
            	new_pos = offset;
            break;
        case 1: /* seek cur */
            new_pos = file->f_pos + offset;
            break;
        case 2: /* seek end */ 
            new_pos = MAX_SIZE - offset;
            break;
    }
    if (new_pos > MAX_SIZE)
        new_pos = MAX_SIZE;
    if (new_pos < 0)
        new_pos = 0;
    file->f_pos = new_pos;
    return new_pos;
}
long device_ioctl(struct file *filp,unsigned int cmd, unsigned long arg)
{
	unsigned char ch;
	int retval = 0;
	long size = _IOC_SIZE(cmd);
        pr_info("%s: Cmd:%u Arg:%lu\n",__func__,cmd,arg);

	if (_IOC_TYPE(cmd) != MSG_MAGIC_NUMBER)	
		return -ENOTTY;	
	if (_IOC_NR(cmd) > MSG_IOCTL_MAX_CMDS)	
		return -ENOTTY;	
	
	retval = access_ok((void __user *)arg, size);	
	
	pr_info("access_ok returned:%d\n",retval);
	if(!retval)
		return -EFAULT;
	
	switch(cmd)
	{
		case MSG_IOCTL_GET_LENGTH:
			pr_info("Get buffer length\n");
			put_user(MAX_SIZE, (unsigned int *)arg);
			break;
		case MSG_IOCTL_CLEAR_BUFFER:
			pr_info("Clear buffer\n");
			memset(kernel_buffer, 0, sizeof(kernel_buffer));
			break;
		case MSG_IOCTL_FILL_BUFFER:
			get_user(ch,(unsigned char *)arg);
			pr_info("fill character:%c\n",ch);
			memset(kernel_buffer, ch, sizeof(kernel_buffer));
			buffer_index = sizeof(kernel_buffer);
			break;
		case MSG_GET_ADDRESS:
			put_user(&kernel_buffer, (unsigned long long *)arg);
			pr_info("MSG_GET_ADDRESS\n");
			break;
		default:
			pr_info("unknown command:%u\n", cmd);
			return -EINVAL;
	}
        return 0;
}


struct file_operations device_fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.llseek = device_lseek,
	.unlocked_ioctl = device_ioctl
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
