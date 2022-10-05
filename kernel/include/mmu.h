#ifndef __MMU_H
#define __MMU_H

#define PGSIZE                  (4096)
#define PTESIZE                 (8) // 64b

#define PGROUNDUP(sz)           (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a)          (((a)) & ~(PGSIZE-1))

// In prot_pg.S, we put kernel stack at 2MB physically, and the size of it is one page
// When we called kinit1, we allocate memory from *end* to *2MB - PGSIZE*, as a scratched
// kernel heap memory.
#define SCRATCH_MAP_START       (0) // pgtbl1 start
#define SCRATCH_MAP_END         (2 << 10 << 10) // pgtbl1 end
#define SCRATCH_KSTACK          (2 << 10 << 10) // kstack1 top
#define SCRATCH_KALLOC_END      (SCRATCH_KSTACK - PGSIZE) // kstack1 bottom, kheap1 top

#define SCRATCH_PGTBL_START     (0x1000)
#define SCRATCH_PGTBL_SZ        (4 * (4 << 10)) // 4 levels * 4KB
#define SCRATCH_PGTBL_END       (SCRATCH_PGTBL_START + SCRATCH_MAP_RANGE)

// page table entries
#define PTE_P                   0x01  // present?
#define PTE_RW                  0x02  // R/W?
#define PTE_US                  0x04  // User/Supervisor?
#define PTE_PWT                 0x08  // write through? (unused)
#define PTE_PCD                 0x10  // cache disable? (unused)
#define PTE_A                   0x20  // accessed?
#define PTE_D                   0x40  // dirty?
#define PTE_PS                  0x80  // 4KB? or 4MB?
#define PTE_G                   0x100 // global? (unused)
#define PTE_PAT                 0x200 // page attribute table?

#endif
