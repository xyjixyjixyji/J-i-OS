#include "include/defs.h"
#include "include/VGA.h"

int
main()
{
    set_cpos(0, 0);
    VGA_clear(COLOR_GREEN, COLOR_BLK);
    const char *info = "Kernel booted with a better VGA buffer...\n";
    VGA_putstr(info, COLOR_GREEN, COLOR_BLK);

    int a = 32;
    VGA_putint(32);

    uart_init();

    return 0;
}
