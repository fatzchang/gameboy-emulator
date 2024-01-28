#ifndef __MEM__
#define __MEM__

#include <stdint.h>

typedef struct MEM {
  int8_t rom1[0x4000];
  int8_t rom2[0x4000];
  int8_t vram[0x1800];
  int8_t bmap[0x800];
  int8_t catram[0x2000];
  int8_t workram[0x2000];
  int8_t echoram[0x1E00];
  int8_t oam[0xA0];
  int8_t unused[0x60];
  int8_t io[0x80];
  int8_t highram[0x7F];
  int8_t interrupt_enable;
} MEM;

void init_mem();

#endif