#ifndef __DEFS_H
#define __DEFS_H

#include "types.h"
#include "interrupts/isr.h"

// VGA.c
void VGA_clear(const u8, const u8);
void VGA_putc(const char, const u8, const u8);
void VGA_putstr(const char*, const u8, const u8);
void VGA_putint(const int, int);
void VGA_panic(const char*);
void VGA_newline();
u16  get_cpos();
void set_cpos(u8, u8);
void show_cursor();
void hide_cursor();
void advance_cpos();
void vga_init();

// port.c
u8 r_port(u16);
void w_port(u16, u8);

// exit.c
void exitvm(u32);

// uart.c
void uart_init();
void uart_putstr(const char*);

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

#endif
