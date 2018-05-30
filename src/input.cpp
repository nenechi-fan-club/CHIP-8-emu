#include "input.h"

input::input() {

}

input::~input() {

}


void input::frame_reset() {
  for (int i = 0; i < KEY_COUNT; i++) {
    keys[i] = false;
  }
}

void input::keydown_event(SDL_Event& e) {
  for (auto bk : bound_keys) {
    if ( e.key.keysym.scancode == bk.second ) {
      keys[bk.first] = true;
      printf("INPUT EVENT ADDED; %d, %d, %d \n", bk.first, bk.second, keys[bk.first]);
    }
  }
}

//void input::keyup_event(SDL_Event& e) {}

bool input::is_keydown(uint8_t key) {
  if ( key > 16) {
    printf("Error! Key > 16\n");
    return false;
  }
  else {
    printf("%d\n", key);
    return keys[key];
  }
}

bool input::is_keyup(uint8_t key) {
  if (key > 16) {
    printf("Error! Key > 16\n");
    return false;
  }
  else {
    if (keys[key])
      return false;

    return true;
  }
}




/*
if( input.is_keydown(v_keys::ONE) ) {
  //do thing
}

*/

void input::bind_default() {
  bound_keys[v_keys::ONE]   = SDL_SCANCODE_1;
  bound_keys[v_keys::TWO]   = SDL_SCANCODE_2;
  bound_keys[v_keys::THREE] = SDL_SCANCODE_3;
  bound_keys[v_keys::C]     = SDL_SCANCODE_4;
  
  bound_keys[v_keys::FOUR]  = SDL_SCANCODE_Q;
  bound_keys[v_keys::FIVE]  = SDL_SCANCODE_W;
  bound_keys[v_keys::SIX]   = SDL_SCANCODE_E;
  bound_keys[v_keys::D]     = SDL_SCANCODE_R;
  
  bound_keys[v_keys::SEVEN] = SDL_SCANCODE_A;
  bound_keys[v_keys::EIGHT] = SDL_SCANCODE_S;
  bound_keys[v_keys::NINE]  = SDL_SCANCODE_D;
  bound_keys[v_keys::E]     = SDL_SCANCODE_F;
  
  bound_keys[v_keys::A]     = SDL_SCANCODE_Z;
  bound_keys[v_keys::ZERO]  = SDL_SCANCODE_X;
  bound_keys[v_keys::B]     = SDL_SCANCODE_C;
  bound_keys[v_keys::F]     = SDL_SCANCODE_V;
}
