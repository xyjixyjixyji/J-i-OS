#ifndef __MMU_H
#define __MMU_H

#define PGSIZE (4096)
#define PTESIZE  (8)

#define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
#define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))

#define SCRATCH_MAP_RANGE (2 << 10 << 10) // 2MB
#define SCRATCH_PA_START  (0x4000)
#define SCRATCH_PA_END (SCRATCH_PA_START + SCRATCH_MAP_RANGE)

#define PTE_P   0x01  // present?
#define PTE_RW  0x02  // R/W?
#define PTE_US  0x04  // User/Supervisor?
#define PTE_PWT 0x08  // write through? (unused)
#define PTE_PCD 0x10  // cache disable? (unused)
#define PTE_A   0x20  // accessed?
#define PTE_D   0x40  // dirty?
#define PTE_PS  0x80  // 4KB? or 4MB?
#define PTE_G   0x100 // global? (unused)
#define PTE_PAT 0x200 // page attribute table?

#endif
