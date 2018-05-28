#pragma once
#include <cstdint>

class chip8 {
public:
  chip8(uint8_t*, uint16_t fsize);
  ~chip8();
public:
  void run_disassembler();

private:
  void disassemble();

private:
  uint8_t* memory;
  uint16_t pc;

  const uint16_t op_start;
  uint16_t op_end;
};