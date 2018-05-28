#include <fstream>
#include <iostream>

#include "src/chip8.h"

int main(int argc, char** argv) {
  chip8 emulator;
  emulator.load_rom(argv[1]);
  emulator.dump_memory();
  printf("\n==================\n\n");
  emulator.run_disassembler();
  return 0;
}