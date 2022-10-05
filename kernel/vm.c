#include "include/defs.h"
#include "include/types.h"
#include "include/x64.h"

// when init() is called, setup the kernel page table and prepare for jump
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
