#include "include/defs.h"
#include "include/x64.h"
#include "include/logger.h"

extern char end[];

void init();

void
_start()
{
    init();
    LOG_INFO("cr3 is at %p", r_cr3());
    LOG_INFO("Initialization Done. Entering J-i-OS");
}

void
init()
{
    LOG_INFO("\n\nJ-i-OS Initializing...");

    LOG_INFO("UART Initialzing...");
    uart_init();

    LOG_INFO("IDT Initialzing...");
    idt_init();

    LOG_INFO("VGA buffer Initializing...");
    vga_init();
}
