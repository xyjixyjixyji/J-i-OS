#include "include/defs.h"

// print and loop
void
panic(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    uart_panic(fmt, ap);
}
