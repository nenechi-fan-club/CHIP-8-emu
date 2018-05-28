#pragma once

#include <cstdint>
#include <string>

const uint16_t ADDR_START = 0x200;
const uint16_t ADDR_END = 0xfff;
const uint8_t REG_SIZE = 16;
const uint8_t STACK_SIZE = 16;

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

private:
  void cycle();
  void disassemble();

//members
private:
  uint8_t* memory;
  uint16_t* sp;
  uint16_t pc;
  uint16_t stack[STACK_SIZE];

  uint16_t len;
  
  uint8_t reg[REG_SIZE];

  uint16_t i;

  uint8_t dt;
  uint8_t st;
};