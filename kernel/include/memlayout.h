#ifndef __MEM_LAYOUT_H
#define __MEM_LAYOUT_H

#define KERNBASE 0x8200
#define PHYSTOP (256 * 1024 * 1024) // 256 MiB RAM

#define USERBASE 0x80000000

// #define V2P(x) (((u64)(x)) - KERNBASE)
// #define P2V(x) ((void *)(((char *)(x)) + KERNBASE))
#define V2P(x) ((u64)(x)) // kernel maintains an identity map
#define P2V(x) ((void *)((char *)(x)))

#endif
