#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("asafravid");
MODULE_DESCRIPTION("A Kernel Module to Intentionally Consume Memory");

#define NUM_PTRS 1024
#define ALLOC_SIZE 4096*1024 // Bytes

int num_ptrs = NUM_PTRS;
int alloc_size = ALLOC_SIZE;

module_param(num_ptrs, int, 0);
module_param(alloc_size, int, 0);

static char** ptrs;

// TODO: ASAFR: Communicate with the kernel module somehow to consume more and more memory

static int __init memconsume_init(void)
{
    int i;

    printk("Module Init: num_ptrs = %d, alloc_size = %d\n", num_ptrs, alloc_size);

    ptrs = (char**)kmalloc(num_ptrs*sizeof(char*), GFP_KERNEL);

    printk(KERN_INFO "Allocated %d (char*)! ptrs=%p\n", num_ptrs, (void*)ptrs);

    for (i = 0; i < num_ptrs; i++) {
        ptrs[i] = kmalloc(alloc_size, GFP_KERNEL);
        printk(KERN_INFO "Allocated %d Bytes! ptrs[%d]=%p\n", alloc_size, i, ptrs[i]);
    }
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit memconsume_cleanup(void)
{
    int i;
    printk(KERN_INFO "Cleaning up module.\n");
    for (i = 0; i < num_ptrs; i++) {
        kfree(ptrs[i]);
        printk(KERN_INFO "Freed %d Bytes! ptrs[%d]=%p\n", alloc_size, i, ptrs[i]);
    }
    kfree(ptrs);
    printk(KERN_INFO "Freed %d (char*)! ptrs=%p\n", num_ptrs, ptrs);
}

module_init(memconsume_init);
module_exit(memconsume_cleanup);

