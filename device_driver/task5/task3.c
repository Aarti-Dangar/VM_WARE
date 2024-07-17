#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEVICE_NAME "pseudo_char_device"
#define BUFFER_SIZE 1024

static int major_number;
static char *device_buffer;
static size_t buffer_size = BUFFER_SIZE;
static size_t buffer_pos = 0;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple pseudo character device driver");

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer, size_t count, loff_t *pos) {
    size_t to_read;
    printk(KERN_INFO "Reading from device\n");

    if (*pos >= buffer_size) {
        return 0;
    }

    to_read = min(count, buffer_size - *pos);
    if (copy_to_user(user_buffer, device_buffer + *pos, to_read)) {
        return -EFAULT;
    }

    *pos += to_read;
    return to_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *pos) {
    size_t to_write;
    printk(KERN_INFO "Writing to device\n");

    if (*pos >= buffer_size) {
        return -ENOMEM;
    }

    to_write = min(count, buffer_size - *pos);
    if (copy_from_user(device_buffer + *pos, user_buffer, to_write)) {
        return -EFAULT;
    }

    *pos += to_write;
    return to_write;
}

static loff_t device_llseek(struct file *file, loff_t offset, int whence) {
    loff_t new_pos;
    printk(KERN_INFO "Seeking in device\n");

    switch (whence) {
        case SEEK_SET:
            new_pos = offset;
            break;
        case SEEK_CUR:
            new_pos = file->f_pos + offset;
            break;
        case SEEK_END:
            new_pos = buffer_size + offset;
            break;
        default:
            return -EINVAL;
    }

    if (new_pos < 0 || new_pos > buffer_size) {
        return -EINVAL;
    }

    file->f_pos = new_pos;
    return new_pos;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_release,
    .read = device_read,
    .write = device_write,
    .llseek = device_llseek,
};

static int __init device_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }

    device_buffer = kmalloc(buffer_size, GFP_KERNEL);
    if (!device_buffer) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to allocate memory for device buffer\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "Registered pseudo char device with major number %d\n", major_number);
    return 0;
}

static void __exit device_exit(void) {
    kfree(device_buffer);
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Unregistered pseudo char device\n");
}

module_init(device_init);
module_exit(device_exit);

