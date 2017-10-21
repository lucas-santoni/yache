#include <iostream>

#include "Yachel.hpp"
#include "MonochromeDisplayKeypad.hpp"

int main(int argc, const char *argv[]) {
  if (argc < 2)
    return Yachel::FAILURE;
  ++argv;

  Yachel::Chip8 chip8;
  try {
    chip8.load(*argv);
  } catch (Yachel::Exceptions::LoaderError& e) {
    std::cout << e.what() << " (" + e.romPath() + ")" << std::endl;
    return Yachel::FAILURE;
  }

  chip8.setClock(400);
  chip8.setTimeout(5);
  sf::MonochromeDisplayKeypad view(Yachel::Specs::WINDOW_WIDTH,
      Yachel::Specs::WINDOW_HEIGHT, 20, "Yache");
  view.setColors(sf::Color(40, 40, 40), sf::Color(168, 153, 132));

  while (view.isOpen()) {
    chip8.tick();
    if (chip8.shouldRedraw())
      view.update(chip8.getScreen());
    view.refresh(chip8);
  }

  return Yachel::SUCCESS;
}
