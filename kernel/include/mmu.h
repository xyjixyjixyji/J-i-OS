#ifndef __MMU_H
#define __MMU_H

#define PGSIZE (4096)
#define PTESIZE (8) // 64b

#define PGROUNDUP(sz) (((sz) + PGSIZE - 1) & ~(PGSIZE - 1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE - 1))

// In prot_pg.S, we put kernel stack at 2MB physically, and the size of it is
// one page When we called kinit1, we allocate memory from *end* to *2MB -
// PGSIZE*, as a scratched kernel heap memory.
#define SCRATCH_MAP_START (0)           // pgtbl1 start
#define SCRATCH_MAP_END (2 << 10 << 10) // pgtbl1 end
#define SCRATCH_KSTACK (2 << 10 << 10)  // kstack1 top
#define SCRATCH_KALLOC_END                                                    \
  (SCRATCH_KSTACK - PGSIZE) // kstack1 bottom, kheap1 top

#define SCRATCH_PGTBL_START (0x1000)
#define SCRATCH_PGTBL_SZ (4 * (4 << 10)) // 4 levels * 4KB
#define SCRATCH_PGTBL_END (SCRATCH_PGTBL_START + SCRATCH_PGTBL_SZ)

// page table entries
//
// SEEK: 47..12 in total 36 bits
// PML4T[47..39] = PDPT
// PDPT[38..30] = PD
// PD[29..21] = PT
// PT[20..12] = PTE -> va
//
// FORMAT
// PML4E: lv4 -> ptr to lv3 table
//    63..52: ...
//    47..12 PML4T physical base addr (9b, 512 entries)
//    11..0:  ...
// PDPTE: lv3 -> ptr to lv2 table
//  format: same above
// PDE: lv2 -> ptr to lv1 table
//  format: same above
// PTE: lv1 -> ptr to va
//  format:
//    63..12: same above
//    11..8:  reserved
//    else below
#define PTE_P 0x01  // present?
#define PTE_RW 0x02 // R/W?
#define PTE_US 0x04 // User/Supervisor?
#define PTE_A 0x20  // accessed?
#define PTE_D 0x40  // dirty?

#define PTE_LV3

#endif
