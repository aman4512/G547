#include <linux/init.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/random.h>
#include <linux/uaccess.h>

static dev_t devt; //Global variable for first device number

static struct cdev c_dev;
static struct class *cls;

//static char   message[256] = {0};
static short  size_of_message;

static int adxl_open(struct inode *, struct file *);
static int adxl_close(struct inode *, struct file *);
static ssize_t adxl_read(struct file *, char *, size_t, loff_t *);
static ssize_t adxl_write(struct file *, const char *, size_t, loff_t *);

int * adxl_output(void)
{
	static int rand[3], adxl_output[3];
	get_random_bytes(&rand[0], 2);
	get_random_bytes(&rand[1], 2);
	get_random_bytes(&rand[2], 2);
	adxl_output[0] = rand[0]/64;
	adxl_output[1] = rand[1]/64;
	adxl_output[2] = rand[2]/64;
	return adxl_output;
}

static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read = adxl_read,
	.release = adxl_close,
	.open = adxl_open,
	.write = adxl_write,
};

static int adxl_init(void)
{
	printk(KERN_INFO "adxl registered\n\n");

	if (alloc_chrdev_region(&devt, 0, 3, "accelerometer_driver") < 0)
	{
		printk(KERN_INFO "Unable to allocate numbers\n");
		return -1;
	}

	if((cls=class_create(THIS_MODULE, "adxl_driver")) == NULL)
	{
		printk(KERN_INFO "Unable to create class\n");
		unregister_chrdev_region(devt, 3);
		return -1;
	}

	if(device_create(cls, NULL, MKDEV(MAJOR(devt),0), NULL, "adxl_x") == NULL)
	{
		printk(KERN_INFO "Unable to create x\n");
		class_destroy(cls);
		unregister_chrdev_region(devt, 3);
		return -1;
	}
	else
		printk(KERN_INFO "x-axis Created\n");

	if(device_create(cls, NULL, MKDEV(MAJOR(devt),1), NULL, "adxl_y") == NULL)
	{
		printk(KERN_INFO "Unable to create y\n");
		class_destroy(cls);
		unregister_chrdev_region(devt, 3);
		return -1;
	}
	else
		printk(KERN_INFO "y-axis Created\n");

	if(device_create(cls, NULL, MKDEV(MAJOR(devt),2), NULL, "adxl_z") == NULL)
	{
		printk(KERN_INFO "Unable to create z\n");
		class_destroy(cls);
		unregister_chrdev_region(devt, 3);
		return -1;
	}
	else
		printk(KERN_INFO "z-axis Created\n");

	cdev_init(&c_dev, &fops);

	if(cdev_add(&c_dev, devt, 3) == -1)
	{
		device_destroy(cls, MKDEV(MAJOR(devt),0));
		device_destroy(cls, MKDEV(MAJOR(devt),1));
		device_destroy(cls, MKDEV(MAJOR(devt),2));
		class_destroy(cls);
		unregister_chrdev_region(devt, 3);
		printk(KERN_INFO "Unable to create cdev\n");
		return -1;
	}

	//printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
	return 0;
}

static void adxl_exit(void)
{
	cdev_del(&c_dev);
	device_destroy(cls, MKDEV(MAJOR(devt),0));
	device_destroy(cls, MKDEV(MAJOR(devt),1));
	device_destroy(cls, MKDEV(MAJOR(devt),2));
	//class_unregister(cls);
	class_destroy(cls);
	unregister_chrdev_region(devt, 3);
	printk(KERN_INFO "adxl unregistered\n\n");
	//return 0;
}

//STEP4: Driver callback functions
static int adxl_open(struct inode *i, struct file *f)
{
	printk(KERN_INFO "adxl: open()\n");
	return 0;
}

static int adxl_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "adxl: close()\n");
	return 0;
}

static ssize_t adxl_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
	int adxl_out[3], *p, i, error_count;
	unsigned int adxl_x, adxl_y, adxl_z;

	p = adxl_output();

	for (i=0; i<3; i++)
	{
		adxl_out[i] = *(p+i);
	}
	error_count = 1;

	adxl_x = adxl_out[0];
	adxl_y = adxl_out[1];
	adxl_z = adxl_out[2];
	
	size_of_message = sizeof(adxl_out);
	// copy_to_user has the format ( * to, *from, size) and returns 0 on success
	error_count = copy_to_user(buffer, &adxl_out, size_of_message);

	if (error_count==0)
	{            // if true then have success
		printk(KERN_INFO "%d %d %d readings\n", adxl_x, adxl_y, adxl_z);
		//return (size_of_message=0);  // clear the position to the start and return 0
   	}
	printk(KERN_INFO "adxl: read()\n");
	return 0;
}

static ssize_t adxl_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "adxl: write()\n");
	return 0;
}

module_init(adxl_init);
module_exit(adxl_exit);

MODULE_DESCRIPTION("adxl driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aman Bhasin <h20180120@goa.bits-pilani.ac.in>");

