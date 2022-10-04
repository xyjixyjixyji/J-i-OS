#include "include/defs.h"

/**
 * Kernel heap memory allocation implementation
 * 
 * The kernel memory are organized in a linked list, each entry represents
 * a single page, PAGESIZE is 4096
 * 
 * The bootloader set a page table in protection mode, layout as follows:
 * PML4T -> 0x1000 (lv4)
 * PDPT  -> 0x2000 (lv3)
 * PDT   -> 0x3000 (lv2)
 * PT    -> 0x4000 (lv1), PT[x] is the actual PTE
 * 
 * From 0x4000, the 2MB are identity mapped, but this is only a scratch pagetable
 * After we allocate some kernel memory based on this pagetable, we will construct
 * a new kernel pagetable at higher address and jump directly to there
 */

// defined in kernel.ld, right after the kernel bss segment
// from here, we can safely alloc heap memory
extern char end[];

struct run {
    struct run *next;
};

// currently only single processor, multi-processor will require locking
struct {
    struct run *free;
} kmem;

u64
kalloc()
{

}

void
kfree(u64 va)
{

}

// we can free 0x4000 -> text, end -> 0x4000 + 2MB
void
kinit_scratch(u64 va_start, u64 va_end)
{

}

void kinit_final(u64 va_start, u64 va_end)
{

}
