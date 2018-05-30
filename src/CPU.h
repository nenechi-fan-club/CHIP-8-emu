#pragma once

#include <array>
#include <cstdint>

#ifndef __GNUG__
#include <random>
#endif

#include "graphics.h"
#include "input.h"

const uint16_t ADDR_START = 0x200;
const uint16_t ADDR_END   = 0xfff;
const uint8_t  REG_SIZE   = 16;
const uint8_t  STACK_SIZE = 16;

//exception in naming scheme, since CPU is an acronym
class CPU {
//Constructors
public:
  CPU();
  ~CPU();

//Methods
public:
  void cycle(uint8_t* memory, uint32_t *pixel_buffer, const input &keypad);

  //should be in its own function and not cycle because it should run on different frequency
  void decrement_timers();

//Members
private:
  uint16_t pc;                 //Program counter
  uint16_t* sp;                 //Stack pointer
  std::array<uint16_t, STACK_SIZE> stack;
  
  //Registers, reg[] are 8 bit registers, i is a special 16 register
  std::array<uint8_t, REG_SIZE> reg;
  uint16_t i;
  
  uint8_t dt;
  uint8_t st;

  #ifndef __GNUG__
  std::mt19937 eng;
  #endif
};
