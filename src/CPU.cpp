#include "CPU.h"
#include <stdio.h>


CPU::CPU() {
  memory = new uint8_t[ADDR_END];
  pc = ADDR_START;
  sp = &stack[0];
}

CPU::~CPU() {
  delete[] memory;
  memory = nullptr;
  sp = nullptr;
}


//nnn or addr - A 12-bit value, the lowest 12 bits of the instruction
//n - A 4-bit value, the lowest 4 bits of the instruction
//x - A 4-bit value, the lower 4 bits of the high byte of the instruction
//y - A 4-bit value, the upper 4 bits of the low byte of the instruction
//kk - An 8-bit value, the lowest 8 bits of the instructiona


void CPU::cycle(uint8_t* memory) {
  uint8_t* opcode = &memory[pc];
  uint8_t first = opcode[0] >> 4;
  uint8_t n = opcode[1] & 0x0f;
  uint8_t x = opcode[0] & 0x0f;
  uint8_t y = (opcode[1] & 0xf0) >> 4;
  uint16_t addr = ((opcode[0] & 0x0f) << 8) | opcode[1];

  pc += 2;

  switch(first) {
    case 0x00:
      switch(opcode[1]) {
        case 0xe0:
          //clear display
        break;
        case 0xee: 
          pc = *sp;
          sp--;
        break;
        default: break;
      }
    break;
    case 0x01: pc = addr; break;
    case 0x02:
      sp++;
      *sp = pc;
      pc = addr;
    break;
    case 0x03: //3xkk: Skip next instruction if Vx == kk
      if (reg[x] == opcode[1]) pc += 2; 
    break;
    case 0x04: //4xkk: Skip next instruction if Vx != kk
      if (reg[x] != opcode[1]) pc += 2; 
    break;
    case 0x05: //5xy0: Skip next instruction if Vx == Vy
      if (reg[x] == reg[y]) pc += 2; 
    break;
    case 0x06: //6xkk: Set Vx = kk
      reg[x] = opcode[1]; 
    break;
    case 0x07: //7xkk: Set Vx = Vx + kk
      reg[x] += opcode[1]; 
    break;
    case 0x08:
      switch(n) {
        case 0x0: //8xy0: Set Vx = Vy
          reg[x] = reg[y];
        break;
        case 0x01: //8xy1: Set Vx = Vx OR Vy
          reg[x] |= reg[y];
        break;
        case 0x02: //8xy2: Set Vx = Vx AND Vy
          reg[x] &= reg[y];
        break;
        case 0x03: { //8xy3: Set Vx = Vx XOR Vy
          reg[x] ^= reg[y];
        } break;
        case 0x04: { //8xy4: Set Vx = Vx + Vy, set Vf = carry
          uint16_t ans = (uint16_t)reg[x] + (uint16_t)reg[y];
          reg[0x0f] = ans > 0xff;
          reg[x] = ans & 0xff;
        } break;
        case 0x05: // 8xy5: Set Vx = Vx - Vy, set Vf = NOT borrow
          reg[0x0f] = reg[x] > reg[y];
          reg[x] -= reg[y];
        break;
        case 0x06: //8xy6: Set Vx = Vx SHR 1
          reg[0x0f] = reg[x] & 0x01;
          reg[x] >>= 1;
        break;
        case 0x07: //8xy7: Set Vx = Vy - Vx, set Vf = NOT borrow
          reg[0x0f] = reg[y] > reg[x];
          reg[x] = reg[y] - reg[x];
        break;
        case 0x0e: //8xye Set Vx = Vx SHL 1
          reg[0x0f] = reg[x] & 0x80;
          reg[x] <<= 1;
        break;
      }
    break;
    case 0x09: //9xy0: Skip next instruction if Vx != Vy
      if (reg[x] != reg[y]) pc += 2;
    break;
    case 0x0a: //Annn: Set I to nnn
      i = addr;
    break;
    case 0x0b: //Bnnn: Jump to V0 + nnn
      pc = addr + (uint16_t)reg[0];
    break;
    case 0x0c: { //Cxkk: Set Vx = random byte & kk
      //std::random_device rd;
      //std::mt19937 gen(rd());
      //std::uniform_int_distribution<int> dist(0, 255);
      //reg[x] = dist(gen) & opcode[1];
    } break;
    case 0x0d: { //Dxyn: Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
    } break;
    case 0x0e: 
      switch(opcode[1]) {
        case 0x9e: //Ex9E: Skip next instruction if key with the value of Vx is pressed
        break;
        case 0xa1: //ExA1: Skip next instruction if key with the value of Vx is not pressed
        break;
      }
    break;
    case 0x0f:
      switch(opcode[1]) {
        case 0x07: //Fx07: Set Vx = delay timer value
          reg[x] = dt;
        break;
        case 0x0a: {
          //capture key
          //reg[x] = key
        } break;
        case 0x15: //Fx15: Set delay timer = Vx
          dt = reg[x];
        break;
        case 0x18: //Set sound timer = Vx
          st = reg[x];
        break;
        case 0x1e: //Set I = I + Vx
          i += reg[x];
        break;
        case 0x29: //Fx29: Set I = location of sprite for digit Vx
        break;
        case 0x33: { //Fx33: Store BCD representation of Vx in memory locations I, I+1, and I+2
          uint8_t t = reg[x];
          for (uint8_t j = 2; j >= 0; j--) {
            memory[i + j] = t % 10;
            t /= 10;
          }
        } break;
        case 0x55: //Fx55: Store registers V0 through Vx in memory starting at location I
          for (uint8_t j = 0; j <= x; j++) {
            memory[i + j] = reg[j];
          }
        break;
        case 0x65: //Fx65: Read registers V0 through Vx from memory starting at location I
          for (uint8_t j = 0; j <= x; j++) {
            reg[j] = memory[i + j];
          }
        break;
      }
    break;
  }
}
