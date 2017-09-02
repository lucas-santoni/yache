#include <fstream>

#include "Chip8.hpp"
#include "status.hpp"
#include "colors.hpp"

Chip8::Chip8(void) :
  _vmemory(Specs::WINDOW_WIDTH, Specs::WINDOW_HEIGHT),
  _window(sf::VideoMode(Specs::WINDOW_WIDTH,
        Specs::WINDOW_HEIGHT), "Yache")
{
  _window.setVerticalSyncEnabled(true);
  _texture.create(Specs::WINDOW_WIDTH, Specs::WINDOW_HEIGHT);
  _sprite.setTexture(_texture);
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

void Chip8::_windowCycle(void) {
  while (_window.pollEvent(_windowEvent)) {
    if (_windowEvent.type == sf::Event::Closed) {
      _window.close();
      exit(SUCCESS);
    }
  }

  if (_redraw) {
    _texture.update(_vmemory.raw());
    _window.clear(sf::Color::Black);
    _window.draw(_sprite);
    _window.display();
  }
}

// TODO: Cleaner error handling
void Chip8::cycle(void) {
  _windowCycle();

  _currentOpcode = _memory[_pc] << 8 | _memory[_pc + 1];
  _pc += 2;

  for (auto& op : _opcodes)
    if ((_currentOpcode & op.mask) == op.key)
      return op.f(this);

  fprintf(stderr, "NON EXISTING OPCODE : 0x%04x\nExiting.\n", _currentOpcode);
  exit(FAILURE);
}
