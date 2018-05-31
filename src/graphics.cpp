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
    SDL_TEXTUREACCESS_STREAMING, 
    CHIP8_WIDTH, CHIP8_HEIGHT);
  if (texture == nullptr) {
    printf("Failed to create texture: %s", SDL_GetError());
    return false;
  }

  /*
    Set the render area to the area of the window
    SDL_Rect{ x, y, w, h };
  */
  render_area = new SDL_Rect{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

  return true;
}

int graphics::update_texture(uint32_t* pixel_buffer) {
  //Lock texture sets &texture_buffer to the address of the texture's data as a linear array
  int pitch; 
  
  if ( SDL_LockTexture(texture, NULL, &texture_buffer, &pitch ) == -1 ) {
    printf( "Error locking texture; SDL_Error: %s\n", SDL_GetError() );
    return -1;
  }
  else {
    // Get data of texture from void* as Uint32 array
    uint32_t* t_buffer = (uint32_t*)texture_buffer;
    if (!t_buffer)
      return 1;

    for (int i = 0; i < (CHIP8_WIDTH * CHIP8_HEIGHT); i++) {
      t_buffer[i] = pixel_buffer[i];
    }
 
    SDL_UnlockTexture(texture);
    t_buffer = nullptr;
    
    return 0;
  } 
}

void graphics::render() {
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, nullptr, render_area);
  SDL_RenderPresent(renderer);
}

int graphics::lock_texture(uint32_t *&pixel_buffer, int *pitch) {
  return SDL_LockTexture(texture, nullptr, reinterpret_cast<void **>(&pixel_buffer), pitch);
}

void graphics::unlock_texture(uint32_t *&pixel_buffer) {
  SDL_UnlockTexture(texture);
  pixel_buffer = nullptr;
}

void graphics::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  delete render_area;
 
  window      = nullptr;
  renderer    = nullptr;
  texture     = nullptr;
  render_area = nullptr;
}
