#include "../includes/Chip8.hpp"

// This opcode is generally not used
void Yachel::Chip8::_op_0NNN(void) {
  return;
}

// Clear the screen
void Yachel::Chip8::_op_00E0(void) {
  for (uint32_t i = 0; i < Yachel::Specs::WINDOW_SIZE; ++i)
    _vram.unsetPixel(i);
}

// Return from subroutine
// Pop address on top of stack onto pc
void Yachel::Chip8::_op_00EE(void) {
  _pc = _stack.top();
  _stack.pop();
}

// Redirect execution flow
// Set pc to raw address
void Yachel::Chip8::_op_1NNN(void) {
  _pc = _arguments.nnn;
}

// Call subroutine
// Push current pc on the stack
void Yachel::Chip8::_op_2NNN(void) {
  if (_stack.size() < Specs::STACK_LIMIT) {
    _stack.push(_pc);
    _pc = _arguments.nnn;
  }
}

// Skip an instruction if a register
// equals value
// Next instruction is generally a jump
void Yachel::Chip8::_op_3XNN(void) {
  if (_registers[_arguments.x] == _arguments.nn)
    _pc += 2;
}

// Same but if not equal
void Yachel::Chip8::_op_4XNN(void) {
  if (_registers[_arguments.x] != _arguments.nn)
    _pc += 2;
}

// Same if register equals register
void Yachel::Chip8::_op_5XY0(void) {
  if (_registers[_arguments.x] == _registers[_arguments.y])
    _pc += 2;
}

// Store value onto register
void Yachel::Chip8::_op_6XNN(void) {
  _registers[_arguments.x] = _arguments.nn;
}

// Add value to register
void Yachel::Chip8::_op_7XNN(void) {
  _registers[_arguments.x] += _arguments.nn;
}

// Register equals other register
void Yachel::Chip8::_op_8XY0(void) {
  _registers[_arguments.x] = _registers[_arguments.y];
}

// Register OR register
void Yachel::Chip8::_op_8XY1(void) {
  _registers[_arguments.x] |= _registers[_arguments.y];
}

// Register AND register
void Yachel::Chip8::_op_8XY2(void) {
  _registers[_arguments.x] &= _registers[_arguments.y];
}

// Register XOR register
void Yachel::Chip8::_op_8XY3(void) {
  _registers[_arguments.x] ^= _registers[_arguments.y];
}

// Addition
// Set register f if carry
void Yachel::Chip8::_op_8XY4(void) {
  int32_t r = _registers[_arguments.x] + _registers[_arguments.y];

  _registers[0xf] = (r > 0xff);
  _registers[_arguments.x] += _registers[_arguments.y];
}

// Soustraction
void Yachel::Chip8::_op_8XY5(void) {
  int32_t r = _registers[_arguments.x] - _registers[_arguments.y];

  _registers[0xf] = (r > 0x0);
  _registers[_arguments.x] -= _registers[_arguments.y];
}

// Get LSB
// Bit shift
void Yachel::Chip8::_op_8XY6(void) {
  bool lsb = _registers[_arguments.y] & true;

  _registers[0xf] = lsb;
  _registers[_arguments.x] = _registers[_arguments.y] >> 0x1;
}

// Another soustraction
void Yachel::Chip8::_op_8XY7(void) {
  int32_t r = _registers[_arguments.y] - _registers[_arguments.x];

  _registers[0xf] = (r > 0x0);
  _registers[_arguments.x] = _registers[_arguments.y] -
    _registers[_arguments.x];
}

// Get MSB
// Bit shift
void Yachel::Chip8::_op_8XYE(void) {
  bool msb = (_registers[_arguments.y] & 0x80) != false;

  _registers[0xf] = msb;
  _registers[_arguments.x] = _registers[_arguments.y] << 1;

}

// If registers differ
// Skip next instructions
void Yachel::Chip8::_op_9XY0(void) {
  if (_registers[_arguments.x] != _registers[_arguments.y])
    _pc += 2;
}

// Hard set index
void Yachel::Chip8::_op_ANNN(void) {
  _index = _arguments.nnn;
}

// Hard set pc
void Yachel::Chip8::_op_BNNN(void) {
  _pc = _registers[0] + _arguments.nnn;
}

// Random
void Yachel::Chip8::_op_CXNN(void) {
  uint8_t r = rand() % 0xff;

  _registers[_arguments.x] = r & _arguments.nn;
}

// This is where the drawing is done
// _redraw is the sentinel which informs
// that the sprite should be refreshed
void Yachel::Chip8::_op_DXYN(void) {
  uint16_t x = _registers[_arguments.x];
  uint16_t y = _registers[_arguments.y];

  _registers[0xf] = false;

  for (auto h = 0; h < _arguments.n; ++h) {
    uint16_t pixel = _ram[_index + h];
    for (auto w = 0; w < 8; ++w) {
      if ((pixel & (0x80 >> w))) {
        if (_vram.isPixelSet(x + w, y + h))
          _registers[0xf] = true;
        _vram.tooglePixel(x + w, y + h);
        _redraw = true;
      }
    }
  }
}

// If a key at register x is pressed,
// skip next instruction
void Yachel::Chip8::_op_EX9E(void) {
  uint8_t k = _registers[_arguments.x];

  if (_keys[k])
    _pc += 2;
}

// If key at register x is not pressed,
// skip next instruction
void Yachel::Chip8::_op_EXA1(void) {
  uint8_t k = _registers[_arguments.x];

  if (!_keys[k]) {
    _pc += 2;
  }
}

// Set register from delay timer
void Yachel::Chip8::_op_FX07(void) {
  _registers[_arguments.x] = _delayTimer;
}

// Wait for a keypress (blocking)
// and store id in register x
void Yachel::Chip8::_op_FX0A(void) {
  if (_keyPressed == Yachel::FAILURE)
    _pc -= 2;
  else
    _registers[_arguments.x] = _keyPressed;
}

// Set delay timer
void Yachel::Chip8::_op_FX15(void) {
  _delayTimer = _registers[_arguments.x];
}

// Set sound timer
void Yachel::Chip8::_op_FX18(void) {
  _soundTimer = _registers[_arguments.x];
}

// Add something to index
void Yachel::Chip8::_op_FX1E(void) {
  _index += _registers[_arguments.x];
}

// Hard set index
void Yachel::Chip8::_op_FX29(void) {
  _index = (_registers[_arguments.x]) * 0x5;
}

// Spread byte in memory
void Yachel::Chip8::_op_FX33(void) {
  _ram[_index] = _registers[_arguments.x] / 100;
  _ram[_index + 1] = (_registers[_arguments.x] / 10) % 10;
  _ram[_index + 2] = _registers[_arguments.x] % 10;
}

// Set portion of memories from register
void Yachel::Chip8::_op_FX55(void) {
  for (auto i = 0; i <= _arguments.x; ++i)
    _ram[_index + i] = _registers[i];

  _index += _arguments.x + 1;
}

// Set registers from a portion of memory
void Yachel::Chip8::_op_FX65(void) {
  for (auto i = 0; i <= _arguments.x; ++i)
    _registers[i] = _ram[_index + i];

  _index += _arguments.x + 1;
}
