#include "Yachel.hpp"
/*#include "MonochromeDisplayKeypad.hpp"

int main(int argc, const char *argv[]) {
  if (argc < 2)
    return Yachel::FAILURE;
  ++argv;

  Yachel::Chip8 chip8;
  chip8.load(*argv);
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
}*/

int main(int argc, const char *argv[]) {
  if (argc < 2)
    return Yachel::FAILURE;
  ++argv;

  Yachel::Chip8 chip8;
  chip8.load(*argv);
  chip8.setClock(400);
  chip8.setTimeout(5);

  Yachel::Debugger debugger(chip8);
  debugger.breakOn(0x200);

  while (true) {
    chip8.tick();
    debugger.update();
  }

  return Yachel::SUCCESS;
} /**/
