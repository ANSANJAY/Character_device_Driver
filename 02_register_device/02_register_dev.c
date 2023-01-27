/*Static method of device number assignment 
 * Kernel will assign the number based on the availabilty
 * int register_chrdev_region (dev_t from,	unsigned count,	const char *name);
 * 
 *	from : the first in the desired range of device numbers; must include the major numbe
 *	count: the number of consecutive device numbers required
 *	name: the name of the device or driver. This will appear in /proc/devices
 *	Return Value:zero on success, a negative error code on failure.


void unregister_chrdev_region(dev_t from, unsigned int count);
 *
 */


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>


int major_number =120;
int minor_number =0;
char *device_name = "mychardev";
int count =1;
dev_t devicenumber;

module_param(major_number,int,0);
module_param(minor_number,int ,0);
module_param(count,int ,0);
module_param(device_name,charp,0);

MODULE_LICENSE("GPL");

static int test_hello_init(void)
{
	devicenumber= MKDEV(major_number, minor_number);
	printk("Major number : %d\n",MAJOR(devicenumber));
	printk("Minor name : %d\n",MINOR(devicenumber));
	printk("Count : %d\n",count);
	printk("Device name : %s\n",device_name);

	if(!register_chrdev_region(devicenumber,count,device_name))
		printk("Device number  registered\n");
	else
		printk("Device number registration failed\n");
	
	return 0;
}

static void test_hello_exit(void)
{
	unregister_chrdev_region(devicenumber,count);
}

module_init(test_hello_init);
module_exit(test_hello_exit);
