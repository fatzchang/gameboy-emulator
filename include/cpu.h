#ifndef __CPU__
#define __CPU__

#include <stdint.h>
#include "mem.h"
#include <stdio.h>
#include "lib/tester.h"

#define BC_ADDR (void *)&cpu.C
#define DE_ADDR (void *)&cpu.E
#define HL_ADDR (void *)&cpu.L
#define SP_ADDR (void *)&cpu.SP

#define BC_VAL ((uint16_t)cpu.B) << 8 | cpu.C
#define HL_VAL ((uint16_t)cpu.H) << 8 | cpu.L

extern struct mem_access mem_accesses[16];
extern int num_mem_accesses;
extern uint8_t *instruction_mem;
extern size_t instruction_mem_size;

typedef struct CPU {
  uint8_t F;
  uint8_t A;
  uint8_t C;
  uint8_t B;
  uint8_t E;
  uint8_t D;
  uint8_t L;
  uint8_t H;

  uint16_t SP;
  uint16_t PC;
} CPU;

extern CPU cpu;
extern MEM mem;

void init_cpu();

static inline void i2r16(uint16_t *r)
{
  extern uint8_t *instruction_mem;
  cpu.PC++;
  *r = *((uint16_t *)(&instruction_mem[cpu.PC]));
  cpu.PC++;
}

// store register to memory
static inline void r2m(uint8_t *r, uint16_t addr)
{
  // printf("addr: 0x%x\n", addr);
  // printf("cpu.A: 0x%x, cpu.B: 0x%x, cpu.C: 0x%x\n", cpu.A, cpu.B, cpu.C);

  ((uint8_t *)(&mem))[addr] = *r;

  // test purpose
  mem_accesses[num_mem_accesses].addr = addr;
  mem_accesses[num_mem_accesses].val = *r;
  mem_accesses[num_mem_accesses].type = MEM_ACCESS_WRITE;
  num_mem_accesses++;

  printf("mem: %d\n\n", ((uint8_t *)(&mem))[addr]);
}

static inline void incr16(void *r)
{
  *((int16_t *)r) = *((int16_t *)r) + 1;
}

static inline void incr8(uint8_t *r)
{
  *r = *r + 1;

  // update flags
  bool z = *r == 0;
  bool c = (cpu.F << 3) >> 7; // c is not affected, store old c
  bool h = (*r & 0x0f) == 0; // low byte carried out
  cpu.F = z << 7;
  cpu.F |= h << 5;
  cpu.F |= c << 4; 
}

static inline void incm(uint16_t addr)
{
  uint8_t v = ((uint8_t *)(&mem))[addr] + 1;
  ((uint8_t *)(&mem))[addr] = v;

#if 1
  // test purpose
  addr = addr % sizeof(instruction_mem_size);
  v = instruction_mem[addr] + 1;
  printf("addr: 0x%x, v: 0x%x, instrmemsize: 0x%lx\n\n", addr, v, instruction_mem_size);
  mem_accesses[num_mem_accesses].addr = addr;
  mem_accesses[num_mem_accesses].type = MEM_ACCESS_WRITE;
  mem_accesses[num_mem_accesses].val = v;
  num_mem_accesses++;
  
#endif

  // update flags
  bool z = v == 0;
  bool c = (cpu.F << 3) >> 7; // c is not affected, store old c
  bool h = (v & 0x0f) == 0; // low byte carried out
  cpu.F = z << 7;
  cpu.F |= h << 5;
  cpu.F |= c << 4; 

}

static inline void exec(int8_t instruction)
{
  switch (instruction)
  {
    // ld $b, $reg8
    case 0x40: cpu.B = cpu.B; break;
    case 0x41: cpu.B = cpu.C; break;
    case 0x42: cpu.B = cpu.D; break;
    case 0x43: cpu.B = cpu.E; break;
    case 0x44: cpu.B = cpu.H; break;
    case 0x45: cpu.B = cpu.L; break;
    case 0x47: cpu.B = cpu.A; break;

    // ld $c, $reg8
    case 0x48: cpu.C = cpu.B; break;
    case 0x49: cpu.C = cpu.C; break;
    case 0x4A: cpu.C = cpu.D; break;
    case 0x4B: cpu.C = cpu.E; break;
    case 0x4C: cpu.C = cpu.H; break;
    case 0x4D: cpu.C = cpu.L; break;
    case 0x4F: cpu.C = cpu.A; break;

    // ld $d, $reg8
    case 0x50: cpu.D = cpu.B; break;
    case 0x51: cpu.D = cpu.C; break;
    case 0x52: cpu.D = cpu.D; break;
    case 0x53: cpu.D = cpu.E; break;
    case 0x54: cpu.D = cpu.H; break;
    case 0x55: cpu.D = cpu.L; break;
    case 0x57: cpu.D = cpu.A; break;

    // ld $e, $reg8
    case 0x58: cpu.E = cpu.B; break;
    case 0x59: cpu.E = cpu.C; break;
    case 0x5A: cpu.E = cpu.D; break;
    case 0x5B: cpu.E = cpu.E; break;
    case 0x5C: cpu.E = cpu.H; break;
    case 0x5D: cpu.E = cpu.L; break;
    case 0x5F: cpu.E = cpu.A; break;

    // ld $h, $reg8
    case 0x60: cpu.H = cpu.B; break;
    case 0x61: cpu.H = cpu.C; break;
    case 0x62: cpu.H = cpu.D; break;
    case 0x63: cpu.H = cpu.E; break;
    case 0x64: cpu.H = cpu.H; break;
    case 0x65: cpu.H = cpu.L; break;
    case 0x67: cpu.H = cpu.A; break;

    // ld $l, $reg8
    case 0x68: cpu.L = cpu.B; break;
    case 0x69: cpu.L = cpu.C; break;
    case 0x6A: cpu.L = cpu.D; break;
    case 0x6B: cpu.L = cpu.E; break;
    case 0x6C: cpu.L = cpu.H; break;
    case 0x6D: cpu.L = cpu.L; break;
    case 0x6F: cpu.L = cpu.A; break;

    // ld $a, $reg8
    case 0x78: cpu.A = cpu.B; break;
    case 0x79: cpu.A = cpu.C; break;
    case 0x7A: cpu.A = cpu.D; break;
    case 0x7B: cpu.A = cpu.E; break;
    case 0x7C: cpu.A = cpu.H; break;
    case 0x7D: cpu.A = cpu.L; break;
    case 0x7F: cpu.A = cpu.A; break;

    case 0x01: i2r16(BC_ADDR); break;
    case 0x11: i2r16(DE_ADDR); break;
    case 0x21: i2r16(HL_ADDR); break;
    case 0x31: i2r16(SP_ADDR); break;

    case 0x02: r2m(&cpu.A, BC_VAL); break;

    case 0x03: incr16(BC_ADDR); break;
    case 0x13: incr16(DE_ADDR); break;
    case 0x23: incr16(HL_ADDR); break;
    case 0x33: incr16(SP_ADDR); break;

    case 0x4: incr8(&cpu.B); break;
    case 0xc: incr8(&cpu.C); break;
    case 0x14: incr8(&cpu.D); break;
    case 0x1c: incr8(&cpu.E); break;
    case 0x24: incr8(&cpu.H); break;
    case 0x2c: incr8(&cpu.L); break;

    case 0x34: incm(HL_VAL); break;
  }
}

static inline void step(uint8_t *mem)
{
  uint8_t instruction = mem[cpu.PC];
  printf("opcode: 0x%x\n", instruction);
  exec(instruction);
  cpu.PC += 1;
}

#endif