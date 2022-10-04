#include "defs.h"

static void
log_string(const char* s)
{
    uart_putstr(s);
}

// print and loop
static void
panic(const char* s)
{
    uart_panic(s);
}
