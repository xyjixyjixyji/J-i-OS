#include "include/defs.h"
#include "include/uart.h"

#define WriteReg(reg, v) (w_port(reg, v))
#define ReadReg(reg) (r_port(reg))

#define WAITFOR(cond) do {while(!(cond));} while(0)

static volatile srlport uart0 = {
    .data = (u16)UART0,
    .inte = (u16)(UART0 + 1),
    .fifo = (u16)(UART0 + 2),
    .line = (u16)(UART0 + 3),
    .modem = (u16)(UART0 + 4),
    .line_stat = (u16)(UART0 + 5),
};

void
uart_init()
{
    // disable interrupts
    WriteReg(uart0.inte, 0x00);
 
    // enable DLAB
    WriteReg(uart0.line, 0x80);

    // baud rate
    WriteReg(uart0.data, 0x03);
    WriteReg(uart0.inte, 0x00);

    // disable DLAB and set data word to 8 bits
    WriteReg(uart0.line, 0x03);

    // enable fifo, clear TX/RX queues and
    // set interrupt watermark at 14 bytes
    WriteReg(uart0.fifo, 0xC7);

    // test the uart
    // set it to loopback mode, and check its register
    WriteReg(uart0.modem, 0x1E);
    WriteReg(uart0.data, 0xAE);
    if(ReadReg(uart0.data) != 0xAE) {
	    // VGA_panic("not the same byte as sent");
    }

    // mark data terminal ready, singal request to send
    // and enable auxilliary output #2 (used as interrupt line for CPU)
    WriteReg(uart0.modem, 0x0B);

    // enable interrupts
    WriteReg(uart0.inte, 0x01);
}

uart_linests_t
uart_lstat()
{
    return ReadReg(uart0.line_stat);
}

static void
uart_sendc(u8 rb)
{
    // BS, del
    if (rb == 8 || rb == 0x7f){
        WAITFOR(uart_lstat() & OUTPUT_EMPTY);
        WriteReg(uart0.data, 8);

        WAITFOR(uart_lstat() & OUTPUT_EMPTY);
        WriteReg(uart0.data, (u8)' ');

        WAITFOR(uart_lstat() & OUTPUT_EMPTY);
        WriteReg(uart0.data, 8);

        return;
    }
    WAITFOR(uart_lstat() & OUTPUT_EMPTY);
    WriteReg(uart0.data, rb);
    // if (!(uart_lstat() & OUTPUT_EMPTY)) {
	//     VGA_putint(123, 10);
    // }
}

void
uart_putstr(const char* s)
{
    while(*s){
        uart_sendc(*s);
        s++;
    }
}

void
uart_putc(int n, int radix)
{
    char str[32];
    itoa(n, str, radix);
    uart_putstr(str);
}
