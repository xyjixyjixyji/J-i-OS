#include "include/defs.h"
#include "include/logger.h"
#include "include/memlayout.h"
#include "include/mmu.h"

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
 * From 0x4000, the 2MB are identity mapped, but this is only a scratch
 * pagetable After we allocate some kernel memory based on this pagetable, we
 * will construct a new kernel pagetable at higher address and jump directly to
 * there
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

// free a range of (vstart, vend)
// if vstart is not page aligned, round up
static void free(char *vstart, char *vend) {
  int npages;
  char *p = (char *)PGROUNDUP((u64)vstart);

  npages = 0;
  for (; p + PGSIZE < vend; p += PGSIZE) {
    kfree(p);
    npages++;
  }

  LOG_INFO("freed %d pages from %p to %p", npages, vstart, vend);
}

// if there is free mem, return va
// else return NULL
char *kalloc() {
  struct run *r;
  r = kmem.free;
  if (r) {
    kmem.free = r->next;
  }
  return (char *)r;
}

// free a page start with va, has to be page aligned
void kfree(char *va) {
  struct run *r;

  // aligned, bounded
  if (va < end || (u64)va >= PHYSTOP || (u64)va % PGSIZE) {
    LOG_DEBUG("va: %p, end: %p, PHYSTOP: %p", va, end, PHYSTOP);
    panic("kfree");
  }

  // junk
  memset(va, 5, PGSIZE);

  r = (struct run *)va;
  r->next = kmem.free;
  kmem.free = r;
}

// end -> 0x4000 + 2MB
void kinit(char *va_start, char *va_end) { free(va_start, va_end); }
