#ifndef __MEM_LAYOUT_H
#define __MEM_LAYOUT_H

//
// Kernel starts at 0x80000000
// ends at PHYSTOP
//
#define KERNBASE 0x80000000
#define PHYSTOP  (KERNBASE + 256*1024*1024) // 256 MiB RAM

#endif
