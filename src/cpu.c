#include "cpu.h"

CPU cpu;

void init_cpu()
{
  cpu.A = 0;
  cpu.F = 0;

  cpu.B = 0;
  cpu.C = 0;

  cpu.D = 0;
  cpu.E = 0;

  cpu.H = 0;
  cpu.L = 0;

  cpu.SP = 0;
  cpu.PC = 0;
}