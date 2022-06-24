#include "../include/types.h"
#include "../include/defs.h"
#include "../include/interrupts/pic.h"

void
io_wait()
{
    w_port(PIC_WAIT_PORT, 0);
}

// we ma ke master holds offset 0, slave holds offset 8
void
pic_remap()
{
    u8 m1, m2;
    m1 = r_port(MPIC_DATA);
    m2 = r_port(SPIC_DATA);

    w_port(MPIC_CMD, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
    io_wait();
	w_port(SPIC_CMD, ICW1_INIT | ICW1_ICW4);
    io_wait();

	w_port(MPIC_DATA, MPIC_OFF);       // ICW2: Master PIC vector offset
    io_wait();
	w_port(SPIC_DATA, SPIC_OFF);       // ICW2: Slave PIC vector offset
    io_wait();

	w_port(MPIC_DATA, 4);       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
	w_port(SPIC_DATA, 2);       // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();
 
	w_port(MPIC_DATA, ICW4_8086);
    io_wait();
	w_port(SPIC_DATA, ICW4_8086);
    io_wait();
 
	w_port(MPIC_DATA, m1);   // restore saved masks.
	w_port(SPIC_DATA, m2);
}

void
end_interrupt(u8 irq)
{
    if(irq >= MPIC_OFF && irq < SPIC_OFF)
        w_port(MPIC_CMD, PIC_EOI);
    else if(irq >= SPIC_OFF && irq < SPIC_OFF+8)
        w_port(SPIC_CMD, PIC_EOI);
    else
        VGA_panic("panic(): unknown irq");
}