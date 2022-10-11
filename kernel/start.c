#include "include/defs.h"
#include "include/logger.h"
#include "include/memlayout.h"
#include "include/mmu.h"
#include "include/x64.h"

extern char end[];
extern char data[];

void ck_invar();
void init();
void kinit1();
void kinit2();
void register_info();

void _start() {
  ck_invar();
  init();
}

void init() {
  KLOG("\n......");
  LOG_INFO("J-i-OS Initializing...");

  LOG_INFO("UART Initialzing...");
  uart_init();

  register_info();

  // 0 ~ 2MB are mapped in prot_pg.S
  LOG_INFO("Freeing from %p to %p", end, (char *)SCRATCH_KALLOC_END);
  kinit1(end, (char *)SCRATCH_KALLOC_END);

  LOG_INFO("Kernel VM Initializing...");
  kvm_init();

  LOG_INFO("IDT Initialzing...");
  idt_init();

  LOG_INFO("VGA buffer Initializing...");
  vga_init();

  LOG_INFO("Freeing from %p to %p", data, (char *)P2V(PHYSTOP >> 2));
  kinit2(SCRATCH_MAP_END, P2V(PHYSTOP >> 2));

  LOG_INFO("Initialization Done. Entering J-i-OS");
}

void ck_invar() {
  if (PHYSTOP >= USERBASE) {
    panic("PHYSTOP >= USERBASE");
  }
}

void kinit1(char *vs, char *ve) { kinit(vs, ve); }
void kinit2(char *vs, char *ve) { kinit(vs, ve); }

void register_info() {
  LOG_WPREFIX("[REGINFO]: ", "cr3 is at %p", r_cr3());
  LOG_WPREFIX("[REGINFO]: ", "rsp is at %p", r_rsp());
}
