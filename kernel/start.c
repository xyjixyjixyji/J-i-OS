#include "include/defs.h"
#include "include/VGA.h"

void
_start()
{
    set_cpos(0, 0);
    VGA_clear(COLOR_GREEN, COLOR_BLK);
    idt_init();
    // uart_init();
    const char *info = "Kernel booted with a better VGA buffer...\n";
    VGA_putstr(info, COLOR_GREEN, COLOR_BLK);
}
