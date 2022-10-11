#include "include/uart.h"

#include "include/defs.h"
#include "include/logger.h"
#include "include/types.h"
#include "stdarg.h"

static char digits[] = "0123456789ABCDEF";

#define WriteReg(reg, v) (w_port(reg, v))
#define ReadReg(reg) (r_port(reg))
#define WAITFOR(cond) \
  do {                \
    while (!(cond))   \
      ;               \
  } while (0)

void uart_vprintf(const char *fmt, va_list ap);

static volatile srlport uart0 = {
    .data = (u16)UART0,
    .inte = (u16)(UART0 + 1),
    .fifo = (u16)(UART0 + 2),
    .line = (u16)(UART0 + 3),
    .modem = (u16)(UART0 + 4),
    .line_stat = (u16)(UART0 + 5),
};

void uart_init() {
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
  if (ReadReg(uart0.data) != 0xAE) {
    // VGA_panic("not the same byte as sent");
  }

  // mark data terminal ready, singal request to send
  // and enable auxilliary output #2 (used as interrupt line for CPU)
  WriteReg(uart0.modem, 0x0B);

  // enable interrupts
  WriteReg(uart0.inte, 0x01);
}

uart_linests_t uart_lstat() { return ReadReg(uart0.line_stat); }

static void uart_sendc(u8 rb) {
  // BS, del
  if (rb == 8 || rb == 0x7f) {
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
}

static void uart_putstr(const char *s) {
  while (*s) {
    uart_sendc(*s);
    s++;
  }
}

static void uart_putint(int n, int radix) {
  char str[32];
  itoa(n, str, radix);
  uart_putstr(str);
}

void uart_panic(const char *fmt, va_list ap) {
  uart_vprintf(fmt, ap);
  while (1)
    ;
}

void uart_printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  uart_vprintf(fmt, ap);
}

void uart_printptr(u64 ptr) {
  int i = 0;
  for (i = 0; i < (sizeof(u64) * 2); i++, ptr <<= 4) {
    char ch = digits[ptr >> 60];
    uart_sendc(ch);
  }
}

// partially from xv6
void uart_vprintf(const char *fmt, va_list ap) {
  char *s;
  int c, i, state;

  state = 0;
  for (i = 0; fmt[i]; i++) {
    c = fmt[i] & 0xff;  // ascii
    if (state == 0) {
      if (c == '%') {
        state = '%';
      } else {
        uart_sendc(c);
      }
    } else if (state == '%') {
      if (c == 'd') {
        int d = va_arg(ap, int);
        uart_putint(d, 10);
      } else if (c == 'x') {
        int h = va_arg(ap, int);
        uart_putint(h, 16);
      } else if (c == 'p') {
        uart_sendc('0');
        uart_sendc('x');
        u64 ptr = va_arg(ap, u64);
        uart_printptr(ptr);
      } else if (c == 's') {
        char *s = va_arg(ap, char *);
        if (s == 0) s = "(null)";
        while (*s != 0) {
          uart_sendc(*s);
          s++;
        }
      } else if (c == 'c') {
        char c = va_arg(ap, int);
        uart_sendc(c);
      } else if (c == '%') {
        uart_sendc(c);
      } else {
        // Unknown % sequence.  Print it to draw attention.
        uart_sendc('%');
        uart_sendc('c');
      }
      state = 0;
    }
  }
  va_end(ap);
}
