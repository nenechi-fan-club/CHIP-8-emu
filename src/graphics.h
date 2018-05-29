#pragma once

#include <cstdint>

#include <SDL.h>

const uint8_t FONT_COUNT = 16;
const uint8_t SPRITE_SIZE = 5;
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

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

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
  
  //TODO(keo): implement texture rendering using lock/unlock
  //int lock_texture(uint32_t *pixel_buffer, int *pitch);
  
  //void unlock_texture();
  void render();
  

private:
  void clean(); //let chip8 clean up?

//members
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};