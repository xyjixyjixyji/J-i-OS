#include "include/defs.h"
#include "include/logger.h"
#include "include/memlayout.h"
#include "include/mmu.h"
#include "include/x64.h"

extern char end[];

void init();
void kinit1();
void register_info();

void
_start()
{
  init();
}

void
init()
{
  KLOG("\n......");
  LOG_INFO("J-i-OS Initializing...");

  LOG_INFO("UART Initialzing...");
  uart_init();

  register_info();

  // 0 ~ 2MB are mapped in prot_pg.S
  LOG_INFO("Mapping from %p to %p", end, (char *)SCRATCH_KALLOC_END);
  kinit1(end, (char *)SCRATCH_KALLOC_END);

  LOG_INFO("IDT Initialzing...");
  idt_init();

  LOG_INFO("VGA buffer Initializing...");
  vga_init();

  LOG_INFO("Initialization Done. Entering J-i-OS");
}

void
kinit1(char *vs, char *ve)
{
  kinit(vs, ve);
}

void
register_info()
{
  LOG_INFO("cr3 is at %p", r_cr3());
  LOG_INFO("rsp is at %p", r_rsp());
}
