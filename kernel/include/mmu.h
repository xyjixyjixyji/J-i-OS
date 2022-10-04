#ifndef __MMU_H
#define __MMU_H

#define PGSIZE (4096)
#define PTESIZE  (8)


// PTE
// 

#define SCRATCH_MAP_RANGE (2 << 10 << 10) // 2MB
#define SCRATCH_PA_START  (0x4000)
#define SCRATCH_PA_END (SCRATCH_PA_START + SCRATCH_MAP_RANGE)

#endif
