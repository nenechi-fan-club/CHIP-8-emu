#pragma once

#include <cstdint>

#include <SDL.h>

const uint8_t FONT_COUNT = 16;
const uint8_t SPRITE_SIZE = 5;
/*
  SUGGESTION: These can be delcared in a linear array and loaded into memory as such,
              as long as the size of the linear array is FONT_COUNT*SPRITE_SIZE.
	      This would probably save on computations, and leave less room for errors.
*/
const uint8_t FONT_SPRITES[FONT_COUNT][SPRITE_SIZE] = {
  {0xf0, 0x90, 0x90, 0x90, 0xf0},
  {0x20, 0x60, 0x20, 0x20, 0x70},
  {0xf0, 0x10, 0xf0, 0x80, 0xf0},
  {0xf0, 0x10, 0xf0, 0x10, 0xf0},
  {0x90, 0x90, 0xf0, 0x10, 0x10},
  {0xf0, 0x80, 0xf0, 0x10, 0xf0},
  {0xf0, 0x80, 0xf0, 0x90, 0xf0},
  {0xf0, 0x10, 0x20, 0x40, 0x40},
  {0xf0, 0x90, 0xf0, 0x90, 0xf0},
  {0xf0, 0x90, 0xf0, 0x10, 0xf0},
  {0xf0, 0x90, 0xf0, 0x90, 0x90},
  {0xe0, 0x90, 0xe0, 0x90, 0xe0},
  {0xf0, 0x80, 0x80, 0x80, 0xf0},
  {0xe0, 0x90, 0x90, 0x90, 0xe0},
  {0xf0, 0x80, 0xf0, 0x80, 0xf0},
  {0xf0, 0x80, 0xf0, 0x80, 0x80}
};

//offset must satisfy: offset + 80 < 512
const uint16_t FONT_OFFSET = 0;

const int CHIP8_WIDTH = 64;
const int CHIP8_HEIGHT = 32;

//TODO(keo): move to graphics class
const int SCALE_FACTOR = 10;

const int WINDOW_WIDTH = CHIP8_WIDTH * SCALE_FACTOR;
const int WINDOW_HEIGHT = CHIP8_HEIGHT * SCALE_FACTOR;

class graphics {
//constructors
public:
  graphics();
  ~graphics();

//methods
public:
  bool init(); 
  
  //wraper for SDL_UpdateTexture
  int update_texture(uint32_t *pixel_buffer);
  /*
    (Sweets): The reason GPU usage is so high, is because SDL_UpdateTexture is an extremely slow function.
              The fix for GPU usage would be to implement this with SDL_LockTexture.
   */
  
  //TODO(keo): implement texture rendering using lock/unlock
  //int lock_texture(uint32_t *pixel_buffer, int *pitch);
  //void unlock_texture();
  
  void render();

private:
  //(Keo): let chip8 clean up?
  void clean();

//members
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};
