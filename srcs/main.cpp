#include "Chip8.hpp"
#include "Status.hpp"

// TODO: clean argument parsing
int main(int argc, char **argv) {
  if (argc < 1)
    return FAILURE;

  Chip8 chip;

  ++argv;
  chip.loadRomFromFile(*argv);
  chip.dumpMemory();

  return SUCCESS;
}
