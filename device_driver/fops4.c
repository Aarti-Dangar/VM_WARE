#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/delay.h>
#include<linux/device.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include<linux/printk.h>
#include<linux/fs.h>
MODULE_LICENSE("GPL");

int base_minor=0;
char *device_name="mychardevfops4";
int count=1;
dev_t devicenumber;


static struct class *class=NULL;
static struct device *device=NULL;
static struct cdev mycdev;
static struct file;
static int device_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n",__func__);

	if((file->f_flags & O_ACCMODE)==O_RDONLY)
	{
		pr_info("opened file in read only mode\n");
	}
	if((file->f_flags & O_ACCMODE)==O_WRONLY)
	{
		pr_info("opened file in write only mode\n");
	}
	//struct inode
	pr_info("Mode:%ho\n",inode->i_mode);
	pr_info("User id=%d\n",inode->i_uid.val);
	pr_info("Group id=%d\n",inode->i_gid.val);
	pr_info("Inode number=%d\n",inode->i_ino);
	pr_info("Major number=%d\tMinor number=%d\n",imajor(inode),iminor(inode));
	pr_info("Major number=%d\tMinor number=%d\n",MAJOR(inode->i_rdev),MINOR(inode->i_rdev));
	
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n",__func__);
	return 0;
}

static ssize_t device_read(struct file *file,char __user *user_buffer,size_t count,loff_t *offset)
{
	pr_info("%s\n",__func__);
	return 0;
}


static ssize_t device_write(struct file *file,const char __user *user_buffer,size_t count,loff_t *offset)
{
	pr_info("%s\n",__func__);
	return count;
}

struct file_operations device_fops =
{
	.read=device_read,
	.write=device_write,
	.open=device_open,
	.release=device_release

};

static int test_hello_init(void)
{

	class = class_create(THIS_MODULE,"myclassfops4");
	printk("device loadded\n");
	if(!alloc_chrdev_region(&devicenumber,base_minor,count,device_name))
	{
		printk("Device number registered\n");
		printk("Major number received:%d\n",MAJOR(devicenumber));
	device = device_create(class,NULL,devicenumber,NULL,device_name);
	cdev_init(&mycdev,&device_fops);
	mycdev.owner=THIS_MODULE;
		cdev_add(&mycdev,devicenumber,count);
	}
	else
printk("device number registration failed\n");
return 0;
}
static void test_hello_exit(void)
{
	unregister_chrdev_region(devicenumber,count);
	cdev_del(&mycdev);
	device_destroy(class,devicenumber);
	class_destroy(class);
printk("Driver unloaded\n");
}
module_init(test_hello_init);
module_exit(test_hello_exit);
