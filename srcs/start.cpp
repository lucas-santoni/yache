#include "Yache.hpp"

int loadRomFromArgs(Yachel::Chip8& chip8,
    int32_t argc, const char *argv[]) {
  if (argc < 2)
    return Yachel::FAILURE;
  ++argv;

  try {
    chip8.load(*argv);
  } catch (Yachel::Exceptions::LoaderError& e) {
    std::cout << e.what() << " (" + e.romPath() + ")" << std::endl;
    return Yachel::FAILURE;
  }

  return Yachel::SUCCESS;
}
