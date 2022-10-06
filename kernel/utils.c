/*
 * change val to a string, stored in buf
 */
#include "include/defs.h"
#include "include/types.h"

void
itoa(int val, char *buf, u8 radix)
{
  char *p;
  char *firstdig;
  char temp;
  unsigned digval;
  p = buf;
  if(val < 0)
    {
      *p++ = '-';
      val = (unsigned long)(-(long)val);
    }
  firstdig = p;
  do
    {
      digval = (unsigned)(val % radix);
      val /= radix;

      if(digval > 9)
        *p++ = (char)(digval - 10 + 'a');
      else
        *p++ = (char)(digval + '0');
    }
  while(val);

  *p-- = '\0';
  do
    {
      temp = *p;
      *p = *firstdig;
      *firstdig = temp;
      --p;
      ++firstdig;
    }
  while(firstdig < p);
}

char *
memset(char *dst, u64 c, u32 nb)
{
  // if dst++, it increments 8 bytes(on 64bit machine)
  if(nb % 8)
    {
      panic("nb is not a multiple of 8");
    }

  u32 i;
  for(i = 0; i < nb / 8; i++)
    {
      dst[i] = (c | (c << 8) | (c << 16) | (c << 24) | (c << 32) | (c << 40)
                | (c << 48) | (c << 56));
    }
  return dst;
}
