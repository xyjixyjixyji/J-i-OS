#include "include/exit.h"
#include "include/defs.h"

void exitvm(u32 exit)
{
    w_port(EXIT_QEMU_PORT, exit);
}
