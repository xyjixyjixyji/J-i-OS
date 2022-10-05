#ifndef __ISR_H
#define __ISR_H

#include "../types.h"

#define NINTRS 64 // # of interrupt handlers

//
// ISRs
//

// this is defined by the process that a ISR is called;
// from bottom up, the registers are push onto stack, and treated
// as the parameter when C function is called.(ABI)
typedef struct __attribute__((packed))
{
  u64 ds;
  u64 rdi, rsi, rbp, rsp, rdx, rcx, rbx, rax;
  u64 intr_nr, err_code;
  u64 rip, cs, eflags, user_rsp, ss;
} isf;

// called by C function, actually code is in isr_wrap.S
extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

extern void isr_32(); // controlled by PIC, timer
extern void isr_33(); // controlled by PIC, keyboard

#define IRQ_DOUBLEFAULT 8
#define IRQ_TIMER 32
#define IRQ_KB IRQ_TIMER + 1

#endif