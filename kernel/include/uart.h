#ifndef __UART_H
#define __UART_H

#include "types.h"

#define UART0	0x3F8

typedef struct __attribute__((packed)){
    u8 data;
    u8 inte;
    u8 fifo;
    u8 line;
    u8 modem;
    u8 line_stat;
} srlport;

typedef u8 uart_linests_t;

/* Line status flag */
#define INPUT_FULL	(1<<0)
#define OUTPUT_EMPTY	(1<<5)

#endif
