//task_16:Implement LKM to print the contents of all the x86_64 registers that the kernel uses, namely cr0, cr2, cr3, cr4 and cr8. Using the value returned from cr4, check if PAE (Physical Address Extension) is enabled on your machine.
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/processor.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aarti");
MODULE_DESCRIPTION("A module to print x86_64 control registers and check PAE.");

// Inline assembly functions to read other control registers

static inline unsigned long read_cr3(void) {
    unsigned long val;
    asm volatile("mov %%cr3, %0" : "=r" (val));
    return val;
}

static inline unsigned long read_cr4(void) {
    unsigned long val;
    asm volatile("mov %%cr4, %0" : "=r" (val));
    return val;
}

static inline unsigned long read_cr8(void) {
    unsigned long val;
    asm volatile("mov %%cr8, %0" : "=r" (val));
    return val;
}


static int __init start(void) {
   unsigned long cr0, cr2, cr3, cr4, cr8;
    cr0 = read_cr0();
    cr2 = read_cr2();
    cr3 = read_cr3();
    cr4 = read_cr4();
    cr8 = read_cr8();

    pr_info("CR0: 0x%lx\n", cr0);
    pr_info("CR2: 0x%lx\n", cr2);
    pr_info("CR3: 0x%lx\n", cr3);
    pr_info("CR4: 0x%lx\n", cr4);
    pr_info("CR8: 0x%lx\n", cr8);

    if (cr4 & X86_CR4_PAE) {
        pr_info("PAE (Physical Address Extension) is enabled.\n");
    } else {
        pr_info("PAE (Physical Address Extension) is not enabled.\n");
    }

    return 0;
}

static void __exit stop(void) {
    pr_info("CR print module unloaded.\n");
}

module_init(start);
module_exit(stop);
/*This kernel module reads the control registers CR0, CR2, CR3, CR4, and CR8, prints their values, and checks if PAE is enabled by examining the PAE bit in the CR4 register. This approach leverages existing kernel functionality and inline assembly to interact with low-level CPU register values from within a Linux kernel module.*/
