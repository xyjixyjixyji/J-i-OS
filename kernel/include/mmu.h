#ifndef __MMU_H
#define __MMU_H

#include "types.h"

#define PGSIZE (4096)
#define PTESIZE (8)  // 64b

#define PGROUNDUP(sz) (((sz) + PGSIZE - 1) & ~(PGSIZE - 1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE - 1))

// In prot_pg.S, we put kernel stack at 2MB physically, and the size of it is
// one page When we called kinit1, we allocate memory from *end* to *2MB -
// PGSIZE*, as a scratched kernel heap memory.
#define SCRATCH_MAP_START (0)            // pgtbl1 start
#define SCRATCH_MAP_END (2 << 10 << 10)  // pgtbl1 end
#define SCRATCH_KSTACK (2 << 10 << 10)   // kstack1 top
#define SCRATCH_KALLOC_END \
  (SCRATCH_KSTACK - PGSIZE)  // kstack1 bottom, kheap1 top

#define SCRATCH_PGTBL_START (0x1000)
#define SCRATCH_PGTBL_SZ (4 * (4 << 10))  // 4 levels * 4KB
#define SCRATCH_PGTBL_END (SCRATCH_PGTBL_START + SCRATCH_PGTBL_SZ)

// page table entries
//
// SEEK: 47..12 in total 36 bits
// PML4T[47..39] = PDPT
// PDPT[38..30] = PD
// PD[29..21] = PT
// PT[20..12] = PTE -> va

#define PTE_P 0x01   // present?
#define PTE_RW 0x02  // R/W?
#define PTE_US 0x04  // User/Supervisor?
#define PTE_A 0x20   // accessed?
#define PTE_D 0x40   // dirty?

typedef unsigned long pml4e_t;
typedef unsigned long pdpte_t;
typedef unsigned long pde_t;
typedef unsigned long pte_t;

//
// +---9---+---9---+---9---+---9---+---12---+
// |  LV4  |  LV3  |  LV2  |  LV1  | Inpage |
// +---9---+---9---+---9---+---9---+---12---+
//
#define V2X_LV4(a) (((u64)(a) >> 39) & 0x1FF)
#define V2X_LV3(a) (((u64)(a) >> 30) & 0x1FF)
#define V2X_LV2(a) (((u64)(a) >> 21) & 0x1FF)
#define V2X_LV1(a) (((u64)(a) >> 12) & 0x1FF)
#define PAGEALIGN(a) ((u64)(a) & ~0xFFF)  // clear last 12 bits

#endif
