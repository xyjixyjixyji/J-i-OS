#include "../include/types.h"
#include "../include/interrupts/isr.h"
#include "../include/interrupts/pic.h"
#include "../include/VGA.h"
#include "../include/defs.h"

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