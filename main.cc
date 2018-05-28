#include <fstream>

#include "src/chip8.hh"

int main() {
  std::ifstream f("roms/pong", std::ios::binary | std::ios::ate);
  uint16_t fsize = f.tellg();
  f.seekg(std::ios_base::beg);

  uint8_t *op = new uint8_t[fsize];
  for (uint16_t i = 0; i < fsize; i++) {
    f >> op[i];
  }

  chip8 emulator(op, fsize);
  emulator.run_disassembler();

  delete []op;
  return 0;
}