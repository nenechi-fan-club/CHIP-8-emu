#include <fstream>
#include <cstdio>

#include <SDL.h>

#include "src/chip8.h"

int main(int argc, char** argv) {
  chip8 emulator;
  if(!emulator.load_rom(argv[1])) {
    printf("Failed to load ROM: file not found\n");
    return 0;
  }

  if(strcmp(argv[2], "-d") == 0) {
    emulator.debug(0);
  } else {
    //emulator.run();
  }

  
  return 0;
}
