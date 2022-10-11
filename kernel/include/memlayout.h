#ifndef __MEM_LAYOUT_H
#define __MEM_LAYOUT_H

#define KERNBASE 0x8200
#define PHYSTOP (256 * 1024 * 1024)  // 256 MiB RAM

// above are for va of user space
#define USERBASE 0x80000000

// kernel maintains an identity map
#define V2P(x) ((u64)(x))
#define P2V(x) ((void *)((char *)(x)))

#endif
