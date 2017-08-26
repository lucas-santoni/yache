#include "Chip8.hpp"
#include "status.hpp"

// TODO: Clean CLI arguments parsing
int main(int argc, char *const argv[]) {
  if (argc < 2)
    return FAILURE;

  Chip8 chip;

  ++argv;
  chip.loadRomFromFile(*argv);

  for (;;)
    chip.cycle();

  return SUCCESS;
}
