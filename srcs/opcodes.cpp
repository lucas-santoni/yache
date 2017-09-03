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
  _pc = _stack.top();
  _stack.pop();
}

void Chip8::_op_1NNN(void) {
  _pc = _currentOpcode & 0x0FFF;
}

void Chip8::_op_2NNN(void) {
  _stack.push(_pc);
  _pc = _currentOpcode & 0x0FFF;
}

void Chip8::_op_3XNN(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  uint8_t nn = _currentOpcode & 0x00FF;

  if (_registers[x] == nn)
    _pc += 2;
}

void Chip8::_op_4XNN(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  uint8_t nn = _currentOpcode & 0x00FF;

  if (_registers[x] != nn)
    _pc += 2;
}

void Chip8::_op_5XY0(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_6XNN(void) {
  _registers[(_currentOpcode & 0x0F00) >> 8] = (_currentOpcode & 0x00FF);
}

void Chip8::_op_7XNN(void) {
  _registers[(_currentOpcode & 0x0F00) >> 8] += _currentOpcode & 0x00FF;
}

void Chip8::_op_8XY0(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  uint8_t y = (_currentOpcode & 0x00F0) >> 4;

  _registers[x] = _registers[y];
}

void Chip8::_op_8XY1(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY2(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  uint8_t y = (_currentOpcode & 0x00F0) >> 4;

  _registers[x] &= _registers[y];
}

void Chip8::_op_8XY3(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_8XY4(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  uint8_t y = (_currentOpcode & 0x00F0) >> 4;
  uint32_t r = _registers[x] + _registers[y];

  _registers[0xf] = (r > 0xff);
  _registers[x] += _registers[y];

}

void Chip8::_op_8XY5(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  uint8_t y = (_currentOpcode & 0x00F0) >> 4;
  uint32_t r = _registers[x] - _registers[y];

  _registers[0xf] = (r > 0x00);
  _registers[x] -= _registers[y];
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
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  uint8_t nn = _currentOpcode & 0x00FF;
  uint8_t r = rand() % (0xff);

  _registers[x] = r & nn;
}

void Chip8::_op_DXYN(void) {
  uint16_t x = _registers[(_currentOpcode & 0x0F00) >> 8];
  uint16_t y = _registers[(_currentOpcode & 0x00F0) >> 4];
  uint16_t n = (_currentOpcode & 0x000F);

  _registers[0xf] = false;
  for (uint32_t h = 0; h < n; ++h) {
    uint16_t pixel = _memory[_index + h];
    for (uint32_t w = 0; w < 8; ++w) {
      if ((pixel & (0x80 >> w)) != 0) {
        if (_vmemory.isSet(x + w, y + h))
          _registers[0xf] = true;
        _vmemory.toogle(x + w, y + h);
      }
    }
  }

  _redraw = true;
}

void Chip8::_op_EX9E(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

// TODO: Check key pressing
void Chip8::_op_EXA1(void) {
  uint8_t x = _registers[(_currentOpcode & 0x0F00) >> 8];

  if (_keys[x])
    _pc += 2;
}

void Chip8::_op_FX07(void) {
  _registers[(_currentOpcode & 0x0F00) >> 8] = _delayTimer;
}

void Chip8::_op_FX0A(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX15(void) {
  _delayTimer = (_currentOpcode & 0x0F00) >> 8;
}

void Chip8::_op_FX18(void) {
  _soundTimer = (_currentOpcode & 0x0F00) >> 8;
}

void Chip8::_op_FX1E(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX29(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;
  _index = _registers[x] * 0x5;
}

void Chip8::_op_FX33(void) {
  _memory[_index] = _registers[(_currentOpcode & 0x0F00) >> 8] / 100;
  _memory[_index + 1] = (_registers[(_currentOpcode &
        0x0F00) >> 8] / 10) % 10;
  _memory[_index + 2] = (_registers[(_currentOpcode &
        0x0F00) >> 8]) % 10;
}

void Chip8::_op_FX55(void) {
  printf("Not implemented.\n");
  exit(SUCCESS);
}

void Chip8::_op_FX65(void) {
  uint8_t x = (_currentOpcode & 0x0F00) >> 8;

  for (uint32_t i = 0; i <= x; ++i)
    _registers[i] = _memory[_index];

  _index += x + 1;
}
