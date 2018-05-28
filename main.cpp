#include <fstream>

#include "src/chip8.h"

int main(int argc, char** argv) {
  
  std::ifstream f(argv[1], std::ios::binary | std::ios::ate);
  int fsize = f.tellg();
  f.seekg(std::ios_base::beg);

  uint8_t* op = new uint8_t[fsize];
  f.read(reinterpret_cast<char *>(op), fsize);
  for (uint16_t i = 0; i < fsize; i++) {
    printf("%02x ", op[i]);
  }

  //print newlines to seperate dissasembly from mixing with the raw hexdump
  printf("\n\n /*************************************/ \n\n");
  
  
  chip8 emulator(op, fsize);
  emulator.run_disassembler();

  delete []op;

  return 0;
}
