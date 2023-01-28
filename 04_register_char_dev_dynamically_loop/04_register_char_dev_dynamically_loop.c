/*
 *fs/char_dev.c
*#define CHRDEV_MAJOR_MAX 512
* Marks the bottom of the first segment of free char majors
*#define CHRDEV_MAJOR_DYN_END 234
* Marks the top and bottom of the second segment of free char majors
*#define CHRDEV_MAJOR_DYN_EXT_START 511
*#define CHRDEV_MAJOR_DYN_EXT_END 384
*
* int alloc_chrdev_region (dev_t *  dev,
		 	unsigned  	baseminor,
 			unsigned  	count,
		 	const char *  	name);
*
*
*
*/


#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/delay.h>
#include<linux/module.h>

dev_t device_number;
int base_minor =0;
int count = 1;
char *device_name= "mydev";

module_param(base_minor,int,0);
module_param(count,int,0);
module_param(device_name,charp,0);

MODULE_LICENSE("GPL");

static int test_hello_init(void)
{

	int i =0;
	
	printk("minor number : %d\n",base_minor);
	printk("count : %d\n",count);
	printk("device name : %s\n",device_name);

	for(i=0;i<512;i++)
	{
		if(!alloc_chrdev_region(&device_number,base_minor,count,device_name))
			{
			printk("device registered\n");
			printk("major number received : %d\n",MAJOR(device_number));
			}

	else{
		printk("Device not registered");
	}
		msleep(1000);
	}

return 0; 
}

static void test_hello_exit(void)
{
	unregister_chrdev_region(device_number,count );
}

module_init(test_hello_init);
module_exit(test_hello_exit);

