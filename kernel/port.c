#include "include/defs.h"
#include "include/types.h"

u8
r_port(u16 port)
{
  u8 val;
  // AT&T syntax reverses the operands
  asm volatile("in %%dx, %%al" : "=a"(val) : "d"(port));
  return val;
}

void
w_port(u16 port, u8 data)
{
  asm volatile("out %%al, %%dx" : : "a"(data), "d"(port));
}
