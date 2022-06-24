#include "include/defs.h"
#include "include/VGA.h"

void
_start()
{
    uart_init();
    idt_init();
    vga_init();

    const char *info = "\nKernel booted with a better VGA buffer...";
    vga_putstr(info);
}
