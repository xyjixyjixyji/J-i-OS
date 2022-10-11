#include "include/defs.h"
#include "include/logger.h"
#include "include/memlayout.h"
#include "include/mmu.h"
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
pml4e_t *kvm_setup() {
  LOG_INFO("Setting up kernel pgtbl");
  pml4e_t *pml4t;
  if ((pml4t = (pml4e_t *)kalloc()) == 0) {
    panic("no kmem for pml4t");
  }
  memset((char *)pml4t, 0, PGSIZE);

  // mappages described above

  return pml4t;
}

// initialization of kernel virtual memory
void kvm_init() {
  pml4e_t *pml4t = kvm_setup();
  LOG_INFO("Switching kernel pgtbl");
  w_cr3((u64)pml4t);
}

// page table walk, from lv4 to pte, return pte
static pte_t *walk(pml4e_t *pml4t, const char *va, int alloc) {
  pml4e_t *pml4e;
  pdpte_t *pdpt;
  pdpte_t *pdpte;
  pde_t *pd;
  pde_t *pde;
  pte_t *pgtbl;

  // walk pml4t
  pml4e = &pml4t[V2X_LV4(va)];
  if (*pml4e & PTE_P) {
    pdpt = (pdpte_t *)P2V(PAGEALIGN(*pml4e));
  } else {
    if (!alloc || (pdpt = (pdpte_t *)kalloc()) == 0) {
      return NULL;
    }
    memset((char *)pdpt, 0, PGSIZE);
    *pml4e = V2P(pdpt) | PTE_P | PTE_RW | PTE_US;
  }

  // walk pdpt
  pdpte = &pdpt[V2X_LV3(va)];
  if (*pdpte & PTE_P) {
    pd = (pdpte_t *)P2V(PAGEALIGN(*pdpte));
  } else {
    if (!alloc || (pd = (pde_t *)kalloc()) == 0) {
      return NULL;
    }
    memset((char *)pd, 0, PGSIZE);
    *pdpte = V2P(pd) | PTE_P | PTE_RW | PTE_US;
  }

  // walk pd
  pde = &pd[V2X_LV2(va)];
  if (*pde & PTE_P) {
    pgtbl = (pte_t *)P2V(PAGEALIGN(*pde));
  } else {
    if (!alloc || (pgtbl = (pte_t *)kalloc()) == 0) {
      return NULL;
    }
    memset((char *)pgtbl, 0, PGSIZE);
    *pde = V2P(pgtbl) | PTE_P | PTE_RW | PTE_US;
  }

  return &pgtbl[V2X_LV1(va)];
}
