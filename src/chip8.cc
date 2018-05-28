#include <iostream>

#include "chip8.hh"

//only loads instructions
chip8::chip8(uint8_t *op, uint16_t fsize): op_start(0x200) {
  op_end = op_start + fsize;
  memory = new uint8_t[op_end];
  memcpy(memory + op_start, op, fsize * sizeof(uint8_t));
}

chip8::~chip8() {
  delete[] memory;
  memory = nullptr;
}

void chip8::disassemble() {
  uint8_t *opcode = &memory[pc];
  uint8_t first = opcode[0] >> 4;
  uint8_t last = opcode[1] & 0x0f;

  printf("%04x %02x %02x ", pc, opcode[0], opcode[1]);

  switch(first) {
    case 0x00:
      //branching
    break;
    case 0x01: {
      uint16_t addr = ((opcode[0] & 0x0f) << 8) | opcode[1];
      printf("%s %03x", "JP", addr);
    }
    break;
    case 0x02: {
      uint16_t addr = ((opcode[0] & 0x0f) << 8) | opcode[1];
      printf("%s %03x", "CALL", addr);
    }
    break;
    case 0x03: {
      uint8_t x = opcode[0] & 0x0f;
      printf("%s V%01x, %02x", "SE", x, opcode[1]);
    }
    break;
    case 0x04: {
      uint8_t x = opcode[0] & 0x0f;
      printf("%s V%01x, %02x", "SNE", x, opcode[1]);
    }
    break;
    case 0x05: {
      if (last == 0) {
      uint8_t x = opcode[0] & 0x0f;
      uint8_t y = (opcode[1] & 0x80) >> 4;
      printf("%s V%01x, V%01x", "SE", x, y);
      } else {
        printf("unknown instruction\n");
      }
    }
    break;
    case 0x06: {
      uint8_t x = opcode[0] & 0x0f;
      printf("%s V%01x, %02x", "LD", x, opcode[1]);
    }
    break;
    case 0x07: {
      uint8_t x = opcode[0] & 0x0f;
      printf("%s V%01x, %02x", "ADD", x, opcode[1]);
    }
    break;
    case 0x08: {
      switch(last) {
        case 0x0: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x, V%01x", "LD", x, y);
        }
        break;
        case 0x01: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x, V%01x", "OR", x, y);
        }
        break;
        case 0x02: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x, V%01x", "AND", x, y);
        }
        break;
        case 0x03: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x, V%01x", "XOR", x, y);
        }
        break;
        case 0x04: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x, V%01x", "ADD", x, y);
        }
        break;
        case 0x05: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x, V%01x", "SUB", x, y);
        }
        break;
        case 0x06: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x {, V%01x}", "SHR", x, y);
        }
        break;
        case 0x07: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x, V%01x", "SUBN", x, y);
        }
        break;
        case 0x0e: {
          uint8_t x = opcode[0] & 0x0f;
          uint8_t y = (opcode[1] & 0x80) >> 4;
          printf("%s V%01x {, V%01x}", "SHL", x, y);
        }
        break;
      }
    }
    break;
    case 0x09: {
      if (last == 0) {
      uint8_t x = opcode[0] & 0x0f;
      uint8_t y = (opcode[1] & 0x80) >> 4;
      printf("%s V%01x, V%01x", "SNE", x, y);
      } else {
        printf("unknown instruction\n");
      }
    }
    break;
    case 0x0a: {
      uint16_t addr = ((opcode[0] & 0x0f) << 8) | opcode[1];
      printf("%s I, %03x", "LD", addr);
    }
    break;
    case 0x0b: {
      uint16_t addr = ((opcode[0] & 0x0f) << 8) | opcode[1];
      printf("%s V0, %03x", "JP", addr);
    }
    break;
    case 0x0c: {
      uint8_t x = opcode[0] & 0x0f;
      printf("%s V%01x, %02x", "RND", x, opcode[1]);
    }
    break;
    case 0x0d: {
      uint8_t x = opcode[0] & 0x0f;
      uint8_t y = (opcode[1] & 0x80) >> 4;
      uint8_t n = opcode[1] & 0x0f;
      printf("%s V%01x, V%01x, %01x", "DRW", x, y, n);
    }
    break;
    case 0x0e: {
      switch(opcode[1]) {
        case 0x9e: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s V%01x", "SKP", x);
        }
        break;
        case 0xa1: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s V%01x", "SKPN", x);
        }
        break;
      }
    }
    break;
    case 0x0f: {
      switch(opcode[1]) {
        case 0x07: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s V%01x, DT", "LD", x);
        }
        break;
        case 0x0a: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s V%01x, K", "LD", x);
        }
        break;
        case 0x15: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s DT, V%01x", "LD", x);
        }
        break;
        case 0x18: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s ST, V%01x", "LD", x);
        }
        break;
        case 0x1e: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s I, V%01x", "ADD", x);
        }
        break;
        case 0x29: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s F, V%01x", "LD", x);
        }
        break;
        case 0x33: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s B, V%01x", "LD", x);
        }
        break;
        case 0x55: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s [I], V%01x", "LD", x);
        }
        break;
        case 0x65: {
          uint8_t x = opcode[0] & 0x0f;
          printf("%s V%01x, [I]", "LD", x);
        }
        break;
      }
    }
    break;
  }
}

void chip8::run_disassembler() {
  pc = op_start;
  while (pc < op_end) {
    disassemble();
    pc += 2;
    printf("\n");
  }
}