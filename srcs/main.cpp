#include "Yache.hpp"
#include "MonochromeDisplayKeypad.hpp"

int main(int argc, const char *argv[]) {
  Yachel::Chip8 chip8;

  if (loadRomFromArgs(chip8, argc, argv) == Yachel::FAILURE)
    return Yachel::FAILURE;

  chip8.setClock(400);
  chip8.setTimeout(5);

  sf::MonochromeDisplayKeypad view(Yachel::Specs::WINDOW_WIDTH,
      Yachel::Specs::WINDOW_HEIGHT, 20, "Yache");
  view.setColors(sf::Color(40, 40, 40), sf::Color(168, 153, 132));

  while (view.isOpen()) {
    try {
      chip8.tick();
    } catch (const Yachel::Exceptions::RuntimeError& e) {
      std::cerr << e.what() << " (0x" << std::hex << e.offset() << ")\n";
    }

    if (chip8.shouldRedraw())
      view.update(chip8.getScreen());
    view.refresh(chip8);
  }

  return Yachel::SUCCESS;
}
