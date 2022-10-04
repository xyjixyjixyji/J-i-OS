#include "include/defs.h"
#include "include/x64.h"
#include "include/stack.h"
#include "include/logger.h"

void init();

void
_start()
{
    init();
    LOG_INFO("Initialization Done. Entering J-i-OS");
}

void
init()
{
    LOG_INFO("\n\nJ-i-OS Initializing...");

    LOG_INFO("Kernel Stack Initializing");
    // kstack_init();

    LOG_INFO("UART Initialzing...");
    uart_init();

    LOG_INFO("IDT Initialzing...");
    idt_init();

    LOG_INFO("VGA buffer Initializing...");
    vga_init();
}
