#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/kmod.h>

#define GPIO_SW 21
#define GPIO_LED 17
#define GPIO_NAME "switch_dev"
#define GPIO_NUM 240
#define IRQF_DISABLED 0x00000020

MODULE_LICENSE("GPL");
struct cdev my_cdev;

static int switch_irq;
char button_status[1024] = "";

static irqreturn_t isr_func(int irq, void *data) {
  if ( irq == switch_irq ) {
    sprintf(button_status, "button: %d", gpio_get_value(GPIO_SW));
    printk(button_status);
  }
  
  return IRQ_HANDLED;
}

int but_open(struct inode *pinode, struct file *pfile) {
  printk(KERN_ALERT "OPEN switch_dev\n");  
  return 0;
}

int but_close(struct inode *pinode, struct file *pfile) {
  printk(KERN_ALERT "RELEASE switch_dev\n");
  return 0;
}

int but_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset) {
  int errcnt = 0;

  errcnt = copy_to_user(buffer, button_status, strlen(button_status));

  if ( errcnt == 0 ) {
    printk("button status sent");
    printk(button_status);
    sprintf(button_status, "button: %d", 0);
  }
  return 0;
}

int device_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset) {
  printk(buffer);
  if ( !strcmp(buffer, "blink") ) {
    gpio_set_value(GPIO_LED, 1);
  }
  else { 
    gpio_set_value(GPIO_LED, 0);
  }
  return 0;
}

struct file_operations fop = {
  .owner = THIS_MODULE,
  .open = but_open,
  .read = but_read,
  .write = device_write,
  .release = but_close,
};

int __init but_init(void) {
  int req;
  
  printk(KERN_INFO "Hello module!\n");
  
  //int devno=GPIO_NUM;
  //alloc_chrdev_region(&devno, 0, 1, GPIO_NAME);
  //MAJOR(devno);
 
  register_chrdev(GPIO_NUM, GPIO_NAME, &fop);
  //cdev_init(&my_cdev, &fop);
  
  gpio_request(GPIO_LED, "LED");
  gpio_direction_output(GPIO_LED, 0);

  gpio_request(GPIO_SW, "SWITCH");
  switch_irq = gpio_to_irq(GPIO_SW);
  req = request_irq(switch_irq, isr_func, IRQF_TRIGGER_RISING | IRQF_DISABLED, "siwtch", NULL);
  
  printk(KERN_INFO "Hello module! Loaded\n");
 
  return 0;
}

void __exit but_exit(void) {
  unregister_chrdev(GPIO_NUM, GPIO_NAME);
  
  free_irq(switch_irq, NULL);
  gpio_free(GPIO_LED);
  gpio_free(GPIO_SW);
  
  printk(KERN_ALERT "EXIT but_dev\n");
}

module_init(but_init);
module_exit(but_exit);
