#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

dev_t dev = 0;


static int major_minor_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Open file\n");
    return 0;
}
ssize_t major_minor_read(struct file *file, char __user *buff, size_t len, loff_t *off)
{
    printk(KERN_INFO "Read file\n");
    return 0;
}
ssize_t major_minor_write(struct file *file, const char __user *buff, size_t len, loff_t *off)
{
    printk(KERN_INFO "Write file\n");
    return 0;
}

int major_minor_release(struct inode * inode, struct file * file)
{
    printk(KERN_INFO "Release file\n");    
    return 0;
}

struct cdev major_minor_cdev;

struct file_operations major_minor_fops =
    {
        .owner = THIS_MODULE,
        .read = major_minor_read,
        .write = major_minor_write,
        .open = major_minor_open,
        .release = major_minor_release
    };

static int __init major_minor_init(void)
{
    int ret = 0;

    printk(KERN_INFO "Init module\n");

    ret = alloc_chrdev_region(&dev, 0, 1, "major_minor_number");

    if (ret)
    {
        printk(KERN_INFO "alloc_chrdev_region failed\n");
        return 1;
    }

    cdev_init(&major_minor_cdev, &major_minor_fops);

    ret = cdev_add(&major_minor_cdev, dev, 1);
    
    if(ret < 0)
    {
        printk(KERN_INFO "Cannot add the device to the system\n");
        goto r_class;
    }

    printk(KERN_INFO "major = %d\n", MAJOR(dev));
    printk(KERN_INFO "minor = %d\n", MINOR(dev));


r_class:
    unregister_chrdev_region(dev,1);

    return 0;
}

static void __exit major_minor_exit(void)
{
    printk(KERN_INFO "Exit module\n");

    unregister_chrdev_region(dev, 1);
}

module_init(major_minor_init);
module_exit(major_minor_exit);

MODULE_AUTHOR("Dinh Dac Cuong");
MODULE_DESCRIPTION("Major and minor testing");
MODULE_LICENSE("GPL");