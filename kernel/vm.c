#include "include/defs.h"
#include "include/types.h"
#include "include/x64.h"

// When calling kvm_setup, we have mapped **end** to 2MB for kernel heap
// now we need to allocate virtual memory for following sections
// todo: 1. user memory (text+data+stack+heap)
//      2. kernel text + rodata
//      3. kernel rwdata + free physical mem
//

// To keep the instruction flow, we maintains an identity map in the kernel
//
// for 2, we can map V:[KERNBASE..data] -> P:[KERNBASE..data] with 0 (no rw)
// this maintains the identity map we made in prot_pg.S
//
// for 3, we can map V:[data..PHYSTOP] -> P:[data..PHYSTOP] (rw)
//
// for further user level program, we allocate memory for them from kernel heap
// but their virtual address should be explicitly shown (like above
// USERBASE...)
//
// In general
// user: from [data..PHYSTOP]
//    - returns a va from kernel (> USERBASE) mapped to a pa from
//    [data..PHYSTOP]
// [KERN_BASE..data] -> [KERN_BASE..data] no_perm
// [data..PHYSTOP]   -> [data..PHYSTOP]   RW_perm
//    - freed in kinit2()

// when init() is called, setup a new kernel page table and prepare for jump
pte_t *
kvm_setup()
{
  return NULL;
}

// initialization of kernel virtual memory
void
kvm_init()
{
  pte_t *dir = kvm_setup();
  w_cr3((u64)dir);
}
