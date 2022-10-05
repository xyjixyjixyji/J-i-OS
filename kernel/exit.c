#include "include/exit.h"
#include "include/defs.h"

// qemu will execute exit(((code << 1) | 1))
void
exitvm(u32 exit)
{
  w_port(EXIT_QEMU_PORT, exit);
}
