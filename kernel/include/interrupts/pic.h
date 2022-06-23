#ifndef __PIC_H
#define __PIC_H

// Programmable Interrupt Controller

// Master PIC controls IRQ 0-7, offset 8
// Slave PIC controls IRQ 8-15, offset 8
// For regular interrupt handling, we need to remap the IRQs

/* IO PORTS */
#define MPIC_CMD    0x20
#define MPIC_DATA   0x21
#define SPIC_CMD    0xA0
#define SPIC_DATA   0xA1
#define PIC_WAIT_PORT 0x80

#define MPIC_OFF 32
#define SPIC_OFF MPIC_OFF+8

/* 
 * Its vector offset. (ICW2)
 * Tell it how it is wired to master/slaves. (ICW3)
 * Gives additional information about the environment. (ICW4)
 */

/* COMMANDS */
#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04	/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08	/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C	/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define PIC_EOI     0x20        /* end of interrupt */

#endif