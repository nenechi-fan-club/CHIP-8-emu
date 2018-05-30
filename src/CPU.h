#pragma once

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
  bool cycle(uint8_t* memory, uint32_t *pixel_buffer, input* k_pad);
  //void start_cpu();

//Members
private:
  uint16_t* sp;                 //Stack pointer
  uint16_t pc;                 //Program counter
  uint16_t stack[STACK_SIZE]; 
  
  uint16_t len;

  //Registers, reg[] are 8 bit registers, i is a special 16 register
  uint8_t reg[REG_SIZE];
  
  uint16_t i;
  
  uint8_t dt;
  uint8_t st;

  #ifndef __GNUG__
  std::mt19937 eng;
  #endif
};
