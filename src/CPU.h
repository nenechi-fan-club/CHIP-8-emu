#pragma once

#include <stdint.h>

const uint16_t ADDR_START = 0x200;
const uint16_t ADDR_END   = 0xfff;
const uint8_t  REG_SIZE   = 16;
const uint8_t  STACK_SIZE = 16;


//exeption in naming scheme, since CPU is an acronym
class CPU {

 private:

  uint8_t* memory;
  uint16_t* sp;                 //Stack pointer
  uint16_t pc;                 //Program counter
  uint16_t stack[STACK_SIZE]; 
  
  uint16_t len;

  //Registers, reg[] are 8 bit registers, i is a special 16 register
  uint8_t reg[REG_SIZE];
  
  uint16_t i;
  
  uint8_t dt;
  uint8_t st;
  

 public:

  CPU();
  ~CPU();

  
  //void start_cpu(  );
  
  
  void cycle(uint8_t* memory);

};
