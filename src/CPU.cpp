#include "CPU.h"

#include <cstdio>

#ifdef __GNUG__
#include <cstdlib>
#include <ctime>
#endif

CPU::CPU() {
  pc = ADDR_START;
  sp = &stack[0];

  //ideally you want to use random device for random number generation because it's non-deterministic but it's not supported by g++
  #ifndef __GNUG__
  std::random_device r 
  eng = std::mt19937(r());
  #else
  srand(time(0));
  #endif
}

CPU::~CPU() {
  sp = nullptr;
}

//nnn or addr - A 12-bit value, the lowest 12 bits of the instruction
//n - A 4-bit value, the lowest 4 bits of the instruction
//x - A 4-bit value, the lower 4 bits of the high byte of the instruction
//y - A 4-bit value, the upper 4 bits of the low byte of the instruction
//kk - An 8-bit value, the lowest 8 bits of the instructiona


//TODO: Ex9E, ExA1, Fx0A
void CPU::cycle(uint8_t* memory, uint32_t* pixel_buffer, const input &keypad ) {
  if (pc >= ADDR_END) {
    printf("out-of-range\n");
    return;
  }

  uint8_t* opcode = &memory[pc];
  uint8_t first = opcode[0] >> 4;
  uint8_t n = opcode[1] & 0x0f;
  uint8_t x = opcode[0] & 0x0f;
  uint8_t y = (opcode[1] & 0xf0) >> 4;
  uint16_t addr = ((opcode[0] & 0x0f) << 8) | opcode[1];

  //printf("pc: %03x\n", pc);
  
  pc += 2;

  switch(first) {
    case 0x00:
      switch(opcode[1]) {
        case 0xe0: //00E0: Clear the display
          memset(pixel_buffer, 0, CHIP8_HEIGHT * CHIP8_WIDTH * sizeof(uint32_t));
        break;
        case 0xee: //00EE: Return from a subroutine
          pc = *sp;
          sp--;
        break;
        default: //0nnn: Jump to a machine code routine at nnn; can be ignored!
        break;
      }
    break;
    case 0x01: //1nnn: Jump to location nnn
      pc = addr; 
    break;
    case 0x02: //2nnn: Call subroutine at nnn
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
      #ifndef __GNUG__
      std::uniform_int_distribution<int> dist(0, 255);
      reg[x] = dist(eng) & opcode[1];
      #else
      reg[x] = rand() % 256 & opcode[1];
      #endif
    } break;
    case 0x0d: { //Dxyn: Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
      uint8_t *sprite = (memory + i);
      for (int j = 0; j < 8; j++) {
        int abs_x = reg[x] + j;
        if (abs_x > CHIP8_WIDTH) abs_x = j;
        //abs_x *= SCALE_FACTOR;
        for (int k = 0; k < n; k++) {
          int abs_y = reg[y] + k;
          if (abs_y > CHIP8_HEIGHT) abs_y = k;
          //abs_y *= SCALE_FACTOR;
          //uint32_t *set = &pixel_buffer[abs_x + abs_y*WINDOW_WIDTH];
          uint32_t *set = &pixel_buffer[abs_x + abs_y*CHIP8_WIDTH];
          uint32_t pixel = (uint32_t)((sprite[k] & (0x80 >> j)) >> (7-j));
          if (pixel) {
            pixel |= 0xffffff;
            reg[0x0f] = uint8_t(*set);
          }

          *set ^= pixel;
          //for (int l = 0; l < SCALE_FACTOR; l++) {
          //  for (int m = 0; m < SCALE_FACTOR; m++) {
          //    *(set + l + m*WINDOW_WIDTH) ^= pixel; 
          //  }
          //}
        }
      }
    } break;
    case 0x0e: 
      switch(opcode[1]) {
        case 0x9e: //Ex9E: Skip next instruction if key with the value of Vx is pressed
        //printf("Warning at %03x: Unimplemented instruction Ex9E\n", pc);
	      if (keypad.is_keydown(reg[x])) {
	        printf("Key '%01x' is down\n", reg[x]);
	        pc += 2;
	      }
        break;
        case 0xa1: //ExA1: Skip next instruction if key with the value of Vx is not pressed
          //printf("Warning at %03x: Unimplemented instruction ExA1\n", pc);
	        if (!keypad.is_keydown(reg[x])) {
	          printf("Key '%01x' is up\n", reg[x]);
	          pc += 2;
	        }
        break;
      }
    break;
    case 0x0f:
      switch(opcode[1]) {
        case 0x07: //Fx07: Set Vx = delay timer value
          reg[x] = dt;
        break;
        case 0x0a: //Fx0A: Wait for a key press, store the value of the key in Vx.
          //printf("Warning at %03x: Unimplemented instruction Fx0A\n", pc);
	        //if(!keypad.is_keydown()) 
          //  pc -= 2;
        break;
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
          i = FONT_OFFSET + reg[x]*SPRITE_SIZE;
        break;
        case 0x33: { //Fx33: Store BCD representation of Vx in memory locations I, I+1, and I+2
          uint8_t t = reg[x];
          for (uint8_t j = 3; j != 0; j--) {
            memory[i + j - 1] = t % 10;
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

void CPU::decrement_timers() {
  if (dt != 0) dt--;
  if (st != 0) st--;
}
