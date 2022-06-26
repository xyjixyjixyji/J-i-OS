#include "../include/types.h"
#include "../include/interrupts/idt.h"
#include "../include/interrupts/pic.h"
#include "../include/VGA.h"
#include "../include/defs.h"

// global variables, static lifetime
idt_gate _IDT[NGATES];
idt_descriptor _IDT_DESCRIPTOR;

// load the IDT, but interrupts are not enabled
// interrupts are enabled after ISR are loaded into IDT
void
idt_load()
{
    _IDT_DESCRIPTOR.off = (u64)&_IDT;
    _IDT_DESCRIPTOR.sz = (NGATES * sizeof(idt_gate)) - 1; // 4096-1
    asm volatile("lidt (%0)":: "r" (&_IDT_DESCRIPTOR));
}

void
set_idt_gate(u8 gate_nr, u64 handler_addr)
{
    u16 lo, mid;
    u32 hi;

    lo = (u16)(handler_addr & 0xFFFF);
    mid = (u16)((handler_addr >> 16) & 0xFFFF);
    hi = (u32)((handler_addr >> 32) & 0xFFFFFFFF);

    idt_gate gate = {
	.off_lo   = lo,
	.cs_sel   = KERNEL_CS_SEL,
	.ist      = 0,
	.attr     = INTR_ATTR,
	.off_mid  = mid,
	.off_hi	  = hi,
	.reserved = 0,
    };

    _IDT[gate_nr] = gate;
}

void
isr_install()
{
    set_idt_gate(0, (u64) isr_0);
    set_idt_gate(1, (u64) isr_1);
    set_idt_gate(2, (u64) isr_2);
    set_idt_gate(3, (u64) isr_3);
    set_idt_gate(4, (u64) isr_4);
    set_idt_gate(5, (u64) isr_5);
    set_idt_gate(6, (u64) isr_6);
    set_idt_gate(7, (u64) isr_7);
    set_idt_gate(8, (u64) isr_8);
    set_idt_gate(9, (u64) isr_9);
    set_idt_gate(10, (u64) isr_10);
    set_idt_gate(11, (u64) isr_11);
    set_idt_gate(12, (u64) isr_12);
    set_idt_gate(13, (u64) isr_13);
    set_idt_gate(14, (u64) isr_14);
    set_idt_gate(15, (u64) isr_15);
    set_idt_gate(16, (u64) isr_16);
    set_idt_gate(17, (u64) isr_17);
    set_idt_gate(18, (u64) isr_18);
    set_idt_gate(19, (u64) isr_19);
    set_idt_gate(20, (u64) isr_20);
    set_idt_gate(21, (u64) isr_21);
    set_idt_gate(22, (u64) isr_22);
    set_idt_gate(23, (u64) isr_23);
    set_idt_gate(24, (u64) isr_24);
    set_idt_gate(25, (u64) isr_25);
    set_idt_gate(26, (u64) isr_26);
    set_idt_gate(27, (u64) isr_27);
    set_idt_gate(28, (u64) isr_28);
    set_idt_gate(29, (u64) isr_29);
    set_idt_gate(30, (u64) isr_30);
    set_idt_gate(31, (u64) isr_31);

    set_idt_gate(32, (u64) isr_32);
    set_idt_gate(33, (u64) isr_33);

    // setup PIC masks
    w_port(MPIC_DATA, 0xfc); //! 0b 1111 1100, only KB and TIMER can happen
    w_port(SPIC_DATA, 0xff); // 0b 1111 1111

    idt_load();
}

void
idt_init()
{
    isr_install();       // install isr
    pic_remap();         // remap IRQs handled by PICs
    isr_registry();      // register handlers to function pointer array
    asm volatile("sti"); // interrupts are enabled from this point
}