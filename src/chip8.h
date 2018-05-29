#pragma once

#include <cstdint>
#include <string>
#include "CPU.h"


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

  void cpu_cycle();
  
private:
  
  void disassemble();

//members
private:

  CPU cpu;
  
  uint8_t* memory;
  uint16_t pc;
  uint16_t len;

};
