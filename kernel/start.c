#include "include/defs.h"
#include "include/exit.h"

void init();

void
_start()
{
    init();

    const char *info = "\nKernel booted with a better VGA buffer...\n";
    uart_printf(info);
    uart_printf("I want %s dollars", "123");
}

void
init()
{
    uart_init();
    idt_init();
    vga_init();
}

void
test()
{

}
