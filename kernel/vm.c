#include "include/types.h"

u64
r_cr3()
{
    u64 val;
    asm volatile ("movq %%cr0, %0": "=r"(val));
    return val;
}

void
w_cr3(u64 val)
{
}
