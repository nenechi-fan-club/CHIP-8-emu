#include <fstream>
#include <iostream>

#include <SDL.h>

#include "src/chip8.h"

int main(int argc, char** argv) {

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    printf( "Error initializing SDL; Error: %s\n", SDL_GetError() );
    return 0;
  }

  SDL_Window* gWindow = SDL_CreateWindow( "CHIP-8", 200, 200, 128, 64, SDL_WINDOW_SHOWN );
  
  chip8 emulator;
  emulator.load_rom(argv[1]);
  emulator.dump_memory();
  printf("\n==================\n\n");
  emulator.run_disassembler();

  emulator.run();

  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;
  
  SDL_Quit();
  
  return 0;
}
