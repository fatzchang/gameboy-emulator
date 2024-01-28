#include <stdint.h>
#include <string.h>
#include "mem.h"

MEM mem;

void init_mem()
{
  // int8_t *ram = (int8_t *)mem;
  memset(&mem, 0, sizeof(mem));
}