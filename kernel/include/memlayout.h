#ifndef __MEM_LAYOUT_H
#define __MEM_LAYOUT_H

//
// Kernel starts at 0x80000000
// ends at PHYSTOP
//
#define KERNBASE 0x8200
#define PHYSTOP  (256*1024*1024) // 256 MiB RAM

#define V2P(x) (((u64)(x)) - KERNBASE)
#define P2V(x) ((void*)(((char *)(x)) + KERNBASE))

#endif
