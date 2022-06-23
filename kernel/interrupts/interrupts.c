#include "../include/types.h"
#include "../include/interrupts/interrupts.h"
#include "../include/interrupts/pic.h"
#include "../include/VGA.h"
#include "../include/defs.h"

// global variables, static lifetime
idt_gate _IDT[NGATES];
idt_descriptor _IDT_DESCRIPTOR;

// See
// https://www.amd.com/system/files/TechDocs/24593.pdf
char *exception_messages[] = {
    "Division by Zero\n",
    "Debug\n",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bat TSS",
    "Segment not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

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

    w_port(MPIC_DATA, 0xfd);
    w_port(SPIC_DATA, 0xff);

    idt_load();
}

void
idt_init()
{
    isr_install();
    // pic_remap();
    asm volatile("sti"); // interrupts are enabled from this point
    VGA_putstr("INTERRUPT ENABLED\n", COLOR_BLUE, COLOR_WHITE);
}

void
doublefault_handler()
{
    VGA_panic("panic(): double fault");
}

void
keyboard_handler()
{
    VGA_putstr("KB", COLOR_WHITE, COLOR_RED);
}

// called from isr_wrap.S, by isr_common
// a naive handler for now, will use intr_nr to multiplex to other C functions
void
isr_handler(isf sf)
{
    const char *msg = exception_messages[sf.intr_nr];
    VGA_putstr(msg, COLOR_WHITE, COLOR_RED);
    VGA_putstr("Errorcode: ", COLOR_WHITE, COLOR_RED);
    VGA_putint(sf.err_code, 16);
    VGA_putc('\n', COLOR_BLK, COLOR_BLUE);
}

