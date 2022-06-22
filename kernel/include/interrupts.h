#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "types.h"

#define KERNEL_CS_SEL	0x08	// 0x0000 1000 => index 1 in gdt => Code Segment
#define INTR_ATTR	0x8E	// INTERRUPT ATTR
#define NGATES		256	// # of entries in idt

typedef struct __attribute__((packed)) {
    u16 off_lo;
    u16 cs_sel;
    u8  ist;
    u8  attr;
    u16 off_mid;
    u32 off_hi;
    u32 reserved;
} idt_gate;

typedef struct __attribute__((packed)) {
    u16 sz;
    u64 off;
} idt_descriptor;

extern idt_gate _IDT[NGATES];
extern idt_descriptor _IDT_DESCRIPTOR;

//
// ISRs
//

// this is defined by the process that a ISR is called;
// from bottom up, the registers are push onto stack, and treated
// as the parameter when C function is called.(ABI)
typedef struct __attribute__((packed)) {
    u64 ds;
    u64 rdi, rsi, rbp, rsp, rdx, rcx, rbx, rax;
    u64 intr_nr, err_code;
    u64 rip, cs, eflags, user_esp, ss;
} reg_ctx;

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

#endif
