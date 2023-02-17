#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("asafravid");
MODULE_DESCRIPTION("A Kernel Module to Intentionally Consume Memory");

#define NUM_PTRS 1024*1024
#define ALLOC_SIZE 4096 // Bytes
static void* ptrs[NUM_PTRS] = {0};

// TODO: ASAFR: Communicate with the kernel module somehow to consume more and more memory

static int __init memconsume_init(void)
{
    int i;
    for (i = 0; i < NUM_PTRS; i++) {
        ptrs[i] = kmalloc(ALLOC_SIZE, GFP_KERNEL);
        printk(KERN_INFO "Allocated %d Bytes! Iteration %d, ptrs[%d]=%p\n", ALLOC_SIZE, i, i, ptrs[i]);
    }
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit memconsume_cleanup(void)
{
    int i;
    printk(KERN_INFO "Cleaning up module.\n");
    for (i = 0; i < NUM_PTRS; i++) {
        kfree(ptrs[i]);
        printk(KERN_INFO "Freed %d Bytes! Iteration %d, ptrs[%d]=%p\n", ALLOC_SIZE, i, i, ptrs[i]);
    }
}

module_init(memconsume_init);
module_exit(memconsume_cleanup);

