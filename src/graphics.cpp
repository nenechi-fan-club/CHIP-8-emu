#include "graphics.h"

#include <cstdio>

graphics::graphics() {}

graphics::~graphics() {
  clean();
}

bool graphics::init() {
  window = SDL_CreateWindow("CHIP-8", 
    200, 200, 
    WINDOW_WIDTH, WINDOW_HEIGHT, 
    SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    printf("Failed to create window: %s", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    printf("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  texture = SDL_CreateTexture(renderer, 
    SDL_PIXELFORMAT_ARGB8888, 
    SDL_TEXTUREACCESS_STATIC, 
    CHIP8_WIDTH, CHIP8_HEIGHT);
  if (texture == nullptr) {
    printf("Failed to create texture: %s", SDL_GetError());
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

  return true;
}

int graphics::update_texture(uint32_t *pixel_buffer) {
  return SDL_UpdateTexture(texture, nullptr, pixel_buffer, CHIP8_WIDTH * sizeof(uint32_t));
}

void graphics::render() {
  SDL_RenderClear(renderer);
  SDL_Rect rect = {.x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT};
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
  SDL_RenderPresent(renderer);
}

//int graphics::lock_texture(uint32_t *pixel_buffer, int *pitch) {
//  return SDL_LockTexture(texture, nullptr, reinterpret_cast<void **>(&pixel_buffer), pitch);
//}

//void graphics::unlock_texture() {
//  SDL_UnlockTexture(texture);
//}

void graphics::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  window = nullptr;
  renderer = nullptr;
  texture = nullptr;
}