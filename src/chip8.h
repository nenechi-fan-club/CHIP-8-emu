#pragma once

#include <cstdint>
#include <string>
#include "CPU.h"


const uint8_t KEY_COUNT = 16;

class chip8 {
//constructors
public:
  chip8();
  ~chip8();

//methods
public:
  void dump_memory(uint16_t offset = ADDR_START);
  void load_rom(std::string rom);
  void run_disassembler();

  //void cpu_cycle();

  void run();
  
private:

  void disassemble();

  void update();
  void render();
  

//members
private:
  CPU cpu;

  bool running = true;
  
  bool keystates[KEY_COUNT];
  
  uint8_t* memory;
  uint16_t pc;
  uint16_t len;
  
};
