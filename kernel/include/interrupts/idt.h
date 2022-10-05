#ifndef __IDT_H
#define __IDT_H

#define KERNEL_CS_SEL 0x08 // 0x0000 1000 => index 1 in gdt => Code Segment
#define INTR_ATTR 0x8E     // INTERRUPT ATTR
#define NGATES 256         // # of entries in idt

typedef struct __attribute__((packed))
{
  u16 off_lo;
  u16 cs_sel;
  u8 ist;
  u8 attr;
  u16 off_mid;
  u32 off_hi;
  u32 reserved;
} idt_gate;

typedef struct __attribute__((packed))
{
  u16 sz;
  u64 off;
} idt_descriptor;

extern idt_gate _IDT[NGATES];
extern idt_descriptor _IDT_DESCRIPTOR;

#endif