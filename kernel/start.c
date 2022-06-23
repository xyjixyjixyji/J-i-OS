#include "include/defs.h"
#include "include/VGA.h"

void
_start()
{
    idt_init();
    uart_init();

    set_cpos(0, 0);
    VGA_clear(COLOR_GREEN, COLOR_BLK);

    const char *info = "Kernel booted with a better VGA buffer...\n";
    uart_putstr(info);
    VGA_putstr(info, COLOR_GREEN, COLOR_BLK);
    VGA_putstr(info, COLOR_GREEN, COLOR_BLK);

    while(1);
}
