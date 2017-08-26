#include <stdlib.h>

#include "Chip8.hpp"
#include "status.hpp"

void Chip8::_op_0NNN(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_00E0(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_00EE(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_1NNN(void) {
  _pc = _currentOpcode & 0x0FFF;
}

void Chip8::_op_2NNN(void) {
  _stack.push(_pc);
  _pc = _currentOpcode & 0x0FFF;
}

void Chip8::_op_3XNN(void) {
  if (_registers[(_currentOpcode & 0x0F00) >> 8] ==
      (_currentOpcode & 0x00FF))
    _pc += 2;
}

void Chip8::_op_4XNN(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_5XY0(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_6XNN(void) {
  _registers[(_currentOpcode & 0x0F00) >> 8] = _currentOpcode & 0x00FF;
}

void Chip8::_op_7XNN(void) {
  _registers[(_currentOpcode & 0x0F00) >> 8] += _currentOpcode & 0x00FF;
}

void Chip8::_op_8XY0(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY1(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY2(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_BXY3(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY4(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY5(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY6(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY7(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XYE(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_9XY0(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_ANNN(void) {
  _index = _currentOpcode & 0x0FFF;
}

void Chip8::_op_BNNN(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_CXNN(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

// TODO: Update video memory
void Chip8::_op_DXYN(void) {
  uint8_t x = _registers[(_currentOpcode & 0x0EFF) >> 8];
  uint8_t y = _registers[(_currentOpcode & 0x00F0) >> 4];
  uint8_t n = (_currentOpcode & 0x000F);

  printf("Draw @ (%x, %x) -> (8, %x)\n", x, y, n);
  _redraw = true;
}

void Chip8::_op_EX9E(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_EXA1(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX07(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX0A(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX15(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX18(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX1E(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX29(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX33(void) {
  _memory[_index] = _registers[(_currentOpcode & 0x0F00) >> 8] / 100;
  _memory[_index + 1] = (_registers[(_currentOpcode &
        0x0F00) >> 8] / 10) % 10;
  _memory[_index + 2] = (_registers[(_currentOpcode &
        0x0F00) >> 8] % 100) % 10;
}

void Chip8::_op_FX55(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX65(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}
