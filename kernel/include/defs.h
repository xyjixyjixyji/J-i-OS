#ifndef __DEFS_H
#define __DEFS_H

#include "stdarg.h"
#include "types.h"
#include "interrupts/isr.h"

// vga.c
void vga_init();
void vga_clear();
void vga_putc(const char);
void vga_putstr(const char*);
void vga_putu64(const u64);

// port.c
u8 r_port(u16);
void w_port(u16, u8);

// exit.c
void exitvm(u32);

// uart.c
void uart_init();
void uart_panic(const char*, va_list ap);
void uart_printf(const char*, ...);
void uart_vprintf(const char*, va_list ap);

// idt.c
void idt_load();
void set_idt_gate(u8, u64);
void isr_install();
void idt_init();

// isr.c
void isr_registry();
void irq_handler(isf);

// pic.c
void pic_remap();
void end_interrupt(u8);

// utils.c
char* itoa(int, char*, unsigned);

// panic.c
void panic(const char*, ...);

#endif
