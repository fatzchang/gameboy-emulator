#include "cpu.h"
#include "mem.h"
#include "lib/tester.h"
#include <string.h>
#include <stdio.h>


size_t instruction_mem_size;
uint8_t *instruction_mem;

int num_mem_accesses;
struct mem_access mem_accesses[16];

/*
 * Called once during startup. The area of memory pointed to by
 * tester_instruction_mem will contain instructions the tester will inject, and
 * should be mapped read-only at addresses [0,tester_instruction_mem_size).
 */
static void cpu_init_hook(size_t tester_instruction_mem_size,
                       uint8_t *tester_instruction_mem)
{
    instruction_mem_size = tester_instruction_mem_size;
    instruction_mem = tester_instruction_mem;

    /* ... Initialize your CPU here ... */
    init_cpu();
    init_mem();
}

/*
 * Resets the CPU state (e.g., registers) to a given state state.
 */
static void cpu_set_state_hook(struct state *state)
{
    (void)state;

    num_mem_accesses = 0;

    /* ... Load your CPU with state as described (e.g., registers) ... */
    cpu.A = state->reg8.A;
    cpu.F = state->reg8.F;

    cpu.B = state->reg8.B;
    cpu.C = state->reg8.C;

    cpu.D = state->reg8.D;
    cpu.E = state->reg8.E;

    cpu.H = state->reg8.H;
    cpu.L = state->reg8.L;

    cpu.SP = state->SP;
    cpu.PC = state->PC;
}

/*
 * Query the current state of the CPU.
 */
static void cpu_get_state_hook(struct state *state)
{
    state->num_mem_accesses = num_mem_accesses;
    memcpy(state->mem_accesses, mem_accesses, sizeof(mem_accesses));

    /* ... Copy your current CPU state into the provided struct ... */
    state->reg8.A = cpu.A;
    state->reg8.F = cpu.F;

    state->reg8.B = cpu.B;
    state->reg8.C = cpu.C;

    state->reg8.D = cpu.D;
    state->reg8.E = cpu.E;

    state->reg8.H = cpu.H;
    state->reg8.L = cpu.L;

    state->SP = cpu.SP;
    state->PC = cpu.PC;

    state->halted = false;
}

/*
 * Step a single instruction of the CPU. Returns the amount of cycles this took
 * (e.g., NOP should return 4).
 */
static int cpu_step_hook(void)
{
    int cycles = 0;

    /* ... Execute a single instruction in your CPU ... */
    step(instruction_mem);

    return cycles;
}

struct tester_operations myops = {
    .init = cpu_init_hook,
    .set_state = cpu_set_state_hook,
    .get_state = cpu_get_state_hook,
    .step = cpu_step_hook,
};

static struct tester_flags flags = {
    .keep_going_on_mismatch = 0,
    .enable_cb_instruction_testing = 1,
    .print_tested_instruction = 1,
    .print_verbose_inputs = 0,
};

int main()
{  
  tester_run(&flags, &myops);

  return 0;
}