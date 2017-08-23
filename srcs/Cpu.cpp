#include "Cpu.hpp"

void Cpu::reset(void) {
  generalRegisters.fill(0);
  callStack.fill(0);
  carry = 0;
  index = 0;
  pc = 0;
  sp = 0;
}
