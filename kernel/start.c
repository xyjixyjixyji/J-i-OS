#include "include/defs.h"
#include "include/VGA.h"

void
_start()
{
    vga_init();
    uart_init();
    idt_init();

    const char *info = "Kernel booted with a better VGA buffer...\n";
    VGA_putstr(info, COLOR_GREEN, COLOR_BLK);

}
