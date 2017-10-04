/*
  COSC1114 Assignment 2
  Author: Rei Ito (s3607050)
  NOTE: Heavily influenced by work done by SolidusCode & Derek Molloy
*/

#include "S3607050Device.h"

// module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rei Ito");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("1.0");

struct cdev *my_cdev; //character device
int major_num; //major number
int ret; //cehcker

dev_t dev_num; //device number

// initialize driver
static int __init my_init(void)
{
  //allocate major number
  ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
  if (ret < 0) { //check valid major number
    printk(KERN_ALERT "S3607050Device: failed to allocate a major number\n");
    return ret;
  }
  major_num = MAJOR(dev_num); //store major number
  printk(KERN_INFO "S3607050Device: major number correctly allocated: %d\n",
    major_num);

  // set up character device
  my_cdev = cdev_alloc();
  my_cdev->ops = &fops;
  my_cdev->owner = THIS_MODULE;

  ret = cdev_add(my_cdev, dev_num, 1); //add character device
  if (ret < 0) { //check valid character device
    printk(KERN_ALERT "S3607050Device: failed to add cdev to kernel\n");
    return ret;
  }
  printk(KERN_INFO "S3607050Device: cdev correctly added to kernel\n");

  sema_init(&my_device.sem, 1);

  // finish message
  printk(KERN_INFO "S3607050Device: module successfully loaded\n");
  return 0;
}

// release driver
static void __exit my_exit(void)
{
  cdev_del(my_cdev); //delete character driver
  unregister_chrdev_region(dev_num, 1); //unregister major number
  printk(KERN_INFO "S3607050Device: module successfully unloaded\n");
}

// open character device driver
static int my_open(struct inode *inodep, struct file *filep)
{
  if (down_interruptible(&my_device.sem) != 0) { //lock device
    printk(KERN_ALERT "S3607050Device: failed to lock device on open\n");
    return -1;
  }

  printk(KERN_INFO "S3607050Device: has successfully opened\n");
  return 0;
}

// read from character device driver to user
static ssize_t my_read(struct file *filep, char *buffer, size_t len,
  loff_t *offset)
{
  printk(KERN_INFO "S3607050Device: reading from device\n");

  // send from character device to user
  ret = copy_to_user(buffer, my_device.data, len);

  if (ret < 0) { //check valid send
    printk(KERN_INFO "S3607050Device: failed to send '%s'(%d) to user\n",
      my_device.data, ret);
    return -EFAULT;
  }

  printk(KERN_INFO "S3607050Device: '%s'(%zu) sent to user\n", my_device.data,
    len);
  return ret;
}


// write to character device driver from user
static ssize_t my_write(struct file *filep, const char *buffer, size_t len,
  loff_t *offset)
{
  printk(KERN_INFO "S3607050Device: writing to device\n");

  // take user input and store
  ret = copy_from_user(my_device.data, buffer, len);
  printk(KERN_INFO "S3607050Device: '%s'(%zu) recieved from user\n",
    my_device.data, len);
  return ret;
}

// close character device driver
static int my_close(struct inode *inodep, struct file *filep)
{
  up(&my_device.sem); //unlock device
  printk(KERN_INFO "S3607050Device: has successfully closed\n");
  return 0;
}

// module controls
module_init(my_init);
module_exit(my_exit);
