#ifndef __STACK_H
#define __STACK_H

#include "x64.h"

#define STACKSIZE 4096

// kernel stack
static char kstack[STACKSIZE];

static inline void
kstack_init()
{
    w_rsp((u64)kstack + STACKSIZE);
}

#endif
