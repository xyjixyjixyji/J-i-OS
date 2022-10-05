#ifndef __JIOS_X64_H
#define __JIOS_X64_H

#include "types.h"

static inline u64
r_cr3()
{
    u64 val;
    asm volatile ("movq %%cr3,%0": "=r"(val));
    return val;
}

static inline u64
r_rsp()
{
    u64 val;
    asm volatile ("movq %%rsp,%0": "=r"(val));
    return val;
}

static inline void
w_cr3(u64 val)
{
    asm volatile("movq %0,%%cr3" : : "r" (val));
}

static inline void
w_rsp(u64 val)
{
    asm volatile("movq %0,%%rsp" : : "r" (val));
}

// todo: tf
struct trapframe {

};

#endif
