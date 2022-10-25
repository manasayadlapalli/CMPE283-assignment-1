#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sai Manasa Yadlapalli");
MODULE_DESCRIPTION("A simple hello world module");
MODULE_VERSION("0.01");

static int __init hello_mod_init(void)
{
        printk(KERN_ALERT "Hello world from kernel!! \n");
        return 0;
}

static void __exit hello_mod_exit(void)
{
        printk(KERN_ALERT "Exiting hello world module from kernel !!!\n");
}

module_init(hello_mod_init);
module_exit(hello_mod_exit);
