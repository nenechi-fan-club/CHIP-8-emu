#pragma once

#include <cstdint>
#include <string>

#include <SDL.h>

#include "CPU.h"
#include "graphics.h"

class chip8 {
//Constructors
public:
  chip8();
  ~chip8();

//Methods
public:
  bool load_rom(std::string rom);

  //void cpu_cycle();

  void run();
  
  void debug(uint16_t offset = ADDR_START);

private:
  //Debug
  void dump_memory(uint16_t offset);
  void disassemble();
  void run_disassembler();

  //SDL
  bool init();
  void update();
  void render();
  void clean();

//Members
private:
  CPU cpu;
  graphics g;

  bool running = true;
  
  uint8_t* memory;
  uint16_t pc;
  uint16_t len;
  
  //GPU memory buffer
  uint32_t *pixel_buffer;
};
