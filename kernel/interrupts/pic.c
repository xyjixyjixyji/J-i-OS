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
    // u8 m1, m2;
    // m1 = r_port(MPIC_DATA);
    // m2 = r_port(SPIC_DATA);

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
 
	w_port(MPIC_DATA, 0);   // restore saved masks.
	w_port(SPIC_DATA, 0);
}

// TODO: add argument to only end one PIC
void
end_interrupt()
{
    w_port(MPIC_CMD, PIC_EOI);
    w_port(SPIC_CMD, PIC_EOI);
}