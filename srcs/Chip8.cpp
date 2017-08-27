#include <fstream>

#include "Chip8.hpp"
#include "status.hpp"
#include "colors.hpp"

Chip8::Chip8(void) :
  _sprite(_texture)
{
  _window.create(sf::VideoMode(Specs::WINDOW_WIDTH,
        Specs::WINDOW_HEIGHT), "Yache");
  _window.setVerticalSyncEnabled(true);

  _texture.create(Specs::WINDOW_WIDTH, Specs::WINDOW_HEIGHT);
}

// TODO: Error handling
void Chip8::loadRomFromFile(const std::string& filePath) {
  std::ifstream rom;

  rom.open(filePath, std::ios::binary);
  if (!rom.good())
    return;

  rom.read(reinterpret_cast<char *>(_memory.data() + Specs::ROM_OFFSET),
      Specs::MEMORY_SIZE);
  rom.close();
}

// TODO: Error handling
void Chip8::dumpMemory(uint32_t from, uint32_t to) const {
  if (from > to || to > Specs::MEMORY_SIZE)
    return;

  uint32_t line = 1;
  for (uint32_t i = from; i < to; ++i) {
    if (line++ % 16 == 0)
      printf("%02x\n", _memory[i]);
    else
      printf("%02x ", _memory[i]);
  }
}

void Chip8::dumpVideoMemory(void) const {
  for (uint32_t i = 0; i < Specs::WINDOW_HEIGHT; ++i) {
    if (_vmemory[i][0].isSet())
      printf("*");
    else
      printf(" ");

    for (uint32_t j = 1; j < Specs::WINDOW_WIDTH; ++j) {
      if (_vmemory[i][j].isSet())
        printf(" *");
      else
        printf(" ");
    }

    if (i != Specs::WINDOW_WIDTH - 1)
      printf("\n");
  }
}

void Chip8::_windowCycle(void) {
  if (!_window.isOpen())
    return;

  while (_window.pollEvent(_windowEvent)) {
    if (_windowEvent.type == sf::Event::Closed) {
      _window.close();
      exit(SUCCESS);
    }
  }

  if (_redraw) {
    _window.clear(sf::Color::Red);
    //_texture.update(_vmemory);
    _window.draw(_sprite);
    _window.display();
  }
}

// TODO: Cleaner error handling
void Chip8::cycle(void) {
  _windowCycle();

  _currentOpcode = _memory[_pc] << 8 | _memory[_pc + 1];

  for (auto& op : _opcodes) {
    if ((_currentOpcode & op.mask) == op.key) {
      //printf("%04x\n", _currentOpcode);
      op.f(this);
      _pc += sizeof(uint16_t);
      return;
    }
  }

  printf("NON EXISTING OPCODE : %04x\n", _currentOpcode);
  exit(FAILURE);
}
