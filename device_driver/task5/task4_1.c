#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define DEVICE_NAME "pseudo_char_device"
#define DEVICE_COUNT 4
#define BUFFER_SIZE 1024

static int major_number;
static char *device_buffers[DEVICE_COUNT];
static size_t buffer_size = BUFFER_SIZE;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A simple pseudo character device driver");

struct pseudo_device_data {
    int minor;
    char *buffer;
    size_t size;
    loff_t position;
};

static struct pseudo_device_data devices[DEVICE_COUNT];

static int device_open(struct inode *inode, struct file *file) {
    int minor = iminor(inode);
    if (minor >= DEVICE_COUNT) {
        return -ENODEV;
    }
    file->private_data = &devices[minor];
    printk(KERN_INFO "Device %d opened\n", minor);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    struct pseudo_device_data *device_data = file->private_data;
    printk(KERN_INFO "Device %d closed\n", device_data->minor);
    return 0;
}

static ssize_t device_read(struct file *file, char __user *user_buffer, size_t count, loff_t *pos) {
    struct pseudo_device_data *device_data = file->private_data;
    size_t to_read;

    if (*pos >= device_data->size) {
        return 0;
    }

    to_read = min(count, device_data->size - *pos);
    if (copy_to_user(user_buffer, device_data->buffer + *pos, to_read)) {
        return -EFAULT;
    }

    *pos += to_read;
    printk(KERN_INFO "Read %zu bytes from device %d\n", to_read, device_data->minor);
    return to_read;
}

static ssize_t device_write(struct file *file, const char __user *user_buffer, size_t count, loff_t *pos) {
    struct pseudo_device_data *device_data = file->private_data;
    size_t to_write;

    if (*pos >= device_data->size) {
        return -ENOMEM;
    }

    to_write = min(count, device_data->size - *pos);
    if (copy_from_user(device_data->buffer + *pos, user_buffer, to_write)) {
        return -EFAULT;
    }

    *pos += to_write;
    printk(KERN_INFO "Wrote %zu bytes to device %d\n", to_write, device_data->minor);
    return to_write;
}

static loff_t device_llseek(struct file *file, loff_t offset, int whence) {
    struct pseudo_device_data *device_data = file->private_data;
    loff_t new_pos;

    switch (whence) {
        case SEEK_SET:
            new_pos = offset;
            break;
        case SEEK_CUR:
            new_pos = file->f_pos + offset;
            break;
        case SEEK_END:
            new_pos = device_data->size + offset;
            break;
        default:
            return -EINVAL;
    }

    if (new_pos < 0 || new_pos > device_data->size) {
        return -EINVAL;
    }

    file->f_pos = new_pos;
    printk(KERN_INFO "Seeked to position %lld in device %d\n", new_pos, device_data->minor);
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
    int i;

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }

    for (i = 0; i < DEVICE_COUNT; i++) {
        device_buffers[i] = kmalloc(buffer_size, GFP_KERNEL);
        if (!device_buffers[i]) {
            int j;
            for (j = 0; j < i; j++) {
                kfree(device_buffers[j]);
            }
            unregister_chrdev(major_number, DEVICE_NAME);
            printk(KERN_ALERT "Failed to allocate memory for device buffer %d\n", i);
            return -ENOMEM;
        }
        devices[i].minor = i;
        devices[i].buffer = device_buffers[i];
        devices[i].size = buffer_size;
        devices[i].position = 0;
        printk(KERN_INFO "Device buffer %d allocated\n", i);
    }

    printk(KERN_INFO "Registered pseudo char device with major number %d\n", major_number);
    return 0;
}

static void __exit device_exit(void) {
    int i;
    for (i = 0; i < DEVICE_COUNT; i++) {
        kfree(device_buffers[i]);
    }
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Unregistered pseudo char device\n");
}

module_init(device_init);
module_exit(device_exit);

