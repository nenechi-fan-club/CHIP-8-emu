#include <algorithm>
#include <cstdio>
#include <cstring>

#include <fstream>
#include <string>
#include <random>

#include "chip8.h"

//load from 0 to 0x200 here
chip8::chip8() {
  memory = new uint8_t[ADDR_END];
  pc = ADDR_START;
}

chip8::~chip8() {
  delete[] memory;
  memory = nullptr;
}

void chip8::load_rom(std::string rom) {
  std::ifstream ifs(rom, std::ios::binary | std::ios::ate);
  len = ifs.tellg();
  ifs.seekg(std::ios_base::beg);
  ifs.read(reinterpret_cast<char *>(memory + ADDR_START), len);
}

void chip8::cpu_cycle() {
  cpu.cycle(memory);
}

//nnn or addr - A 12-bit value, the lowest 12 bits of the instruction
//n - A 4-bit value, the lowest 4 bits of the instruction
//x - A 4-bit value, the lower 4 bits of the high byte of the instruction
//y - A 4-bit value, the upper 4 bits of the low byte of the instruction
//kk - An 8-bit value, the lowest 8 bits of the instructiona

void chip8::disassemble() {
  uint8_t* opcode = &memory[pc];
  uint8_t first = opcode[0] >> 4;
  uint8_t n = opcode[1] & 0x0f;
  uint8_t x = opcode[0] & 0x0f;
  uint8_t y = (opcode[1] & 0xf0) >> 4;
  uint16_t addr = ((opcode[0] & 0x0f) << 8) | opcode[1];
  
  printf("%03x %02x %02x ", pc, opcode[0], opcode[1]);

  switch(first) {
    case 0x00: 
      switch(opcode[1]) {
        case 0xe0: printf("CLS"); break;
        case 0xee: printf("RET"); break;
        default: printf("%s %03x", "SYS", addr); break;
      }
    break;
    case 0x01: printf("%s %03x", "JP", addr); break;
    case 0x02: printf("%s %03x", "CALL", addr); break;
    case 0x03: printf("%s V%01x, %02x", "SE", x, opcode[1]); break;
    case 0x04: printf("%s V%01x, %02x", "SNE", x, opcode[1]); break;
    case 0x05: printf("%s V%01x, V%01x", "SE", x, y); break;
    case 0x06: printf("%s V%01x, %02x", "LD", x, opcode[1]); break;
    case 0x07: printf("%s V%01x, %02x", "ADD", x, opcode[1]); break;
    case 0x08:
      switch(n) {
        case 0x00: printf("%s V%01x, V%01x", "LD", x, y); break;
        case 0x01: printf("%s V%01x, V%01x", "OR", x, y); break;
        case 0x02: printf("%s V%01x, V%01x", "AND", x, y); break;
        case 0x03: printf("%s V%01x, V%01x", "XOR", x, y); break;
        case 0x04: printf("%s V%01x, V%01x", "ADD", x, y); break;
        case 0x05: printf("%s V%01x, V%01x", "SUB", x, y); break;
        case 0x06: printf("%s V%01x {, V%01x}", "SHR", x, y); break;
        case 0x07: printf("%s V%01x, V%01x", "SUBN", x, y); break;
        case 0x0e: printf("%s V%01x {, V%01x}", "SHL", x, y); break;
      }
    break;
    case 0x09: printf("%s V%01x, V%01x", "SNE", x, y); break;
    case 0x0a: printf("%s I, %03x", "LD", addr); break;
    case 0x0b: printf("%s V0, %03x", "JP", addr); break;
    case 0x0c: printf("%s V%01x, %02x", "RND", x, opcode[1]); break;
    case 0x0d: printf("%s V%01x, V%01x, %01x", "DRW", x, y, n); break;
    case 0x0e:
      switch(opcode[1]) {
        case 0x9e: printf("%s V%01x", "SKP", x); break;
        case 0xa1: printf("%s V%01x", "SKPN", x); break;
      }
    break;
    case 0x0f:
      switch(opcode[1]) {
        case 0x07: printf("%s V%01x, DT", "LD", x); break;
        case 0x0a: printf("%s V%01x, K", "LD", x); break;
        case 0x15: printf("%s DT, V%01x", "LD", x); break;
        case 0x18: printf("%s ST, V%01x", "LD", x); break;
        case 0x1e: printf("%s I, V%01x", "ADD", x); break;
        case 0x29: printf("%s F, V%01x", "LD", x); break;
        case 0x33: printf("%s B, V%01x", "LD", x); break;
        case 0x55: printf("%s [I], V%01x", "LD", x); break;
        case 0x65: printf("%s V%01x, [I]", "LD", x); break;
      }
    break;
  }
}

void chip8::dump_memory(uint16_t offset) {
  uint16_t end = std::min<int16_t>(ADDR_END, offset + len);
  for (uint16_t j = offset; j < end; j += 0x10) {
    printf("%03x  ", j);
    for (uint16_t k = 0; k < 0x10 && k + j < end; k++) {
      printf("%02x ", memory[k + j]);
    }
    printf("\n");
  }
}

void chip8::run_disassembler() {
  pc = ADDR_START;
  while (pc < ADDR_START + len) {
    disassemble();
    pc += 2;
    printf("\n");
  }
}
