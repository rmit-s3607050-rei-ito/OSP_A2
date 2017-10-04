/*
  COSC1114 Assignment 2
  Author: Rei Ito (s3607050)
  NOTE: Heavily influenced by work done by SolidusCode & Derek Molloy
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "S3607050Device" //device name

struct virtual_device {
  char data[100]; //message size
  struct semaphore sem;
} my_device; //device structure

// function prototypes
static int my_open(struct inode *, struct file *);
static ssize_t my_read(struct file *, char *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char *, size_t, loff_t *);
static int my_close(struct inode *, struct file *);

// device operations
struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = my_open,
  .read = my_read,
  .write = my_write,
  .release = my_close,
};

// module function prototypes
static int __init my_init(void);
static void __exit my_exit(void);
