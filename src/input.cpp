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

void input::keyup_event(SDL_Event& e) {

  for (auto bk : bound_keys) {
    if ( e.key.keysym.scancode == bk.second ) {
      keys[bk.first] = false;
       printf("KEYUP EVENT; %d, %d, %d \n", bk.first, bk.second, keys[bk.first]);
    }
  }

}

bool input::is_keydown(uint8_t key) {
  if ( key > 16) {
    printf("Error! Key > 16\n");
    return false;
  }
  else {
    return keys[key];
  }
}

bool input::is_keyup(uint8_t key) {
  if (key > 16) {
    printf("Error! Key > 16\n");
    return false;
  }
  else {
    if (keys[key]) {
      return false;
    }
    else {
      return true;
    }
  }
}



void input::log_inputs() {
  bool log = false;
  for (int i = 0; i < KEY_COUNT; i++) {
    if (i == 1) {
      log == true;
      break;
    }
  }
  if (log) {
    for (int i = 0; i < KEY_COUNT; i++) {
      printf(" key: %d, bool: %d\n", i, keys[i]);
    }
  }
}


void input::set_binding() {
  bound_keys = bind_default();
}

 

std::map<uint8_t, SDL_Scancode> input::bind_default() {
  std::map<uint8_t, SDL_Scancode> default_keys;
  
  default_keys[v_keys::ONE]   = SDL_SCANCODE_1;
  default_keys[v_keys::TWO]   = SDL_SCANCODE_2;
  default_keys[v_keys::THREE] = SDL_SCANCODE_3;
  default_keys[v_keys::C]     = SDL_SCANCODE_4;
  
  default_keys[v_keys::FOUR]  = SDL_SCANCODE_Q;
  default_keys[v_keys::FIVE]  = SDL_SCANCODE_W;
  default_keys[v_keys::SIX]   = SDL_SCANCODE_E;
  default_keys[v_keys::D]     = SDL_SCANCODE_R;
  
  default_keys[v_keys::SEVEN] = SDL_SCANCODE_A;
  default_keys[v_keys::EIGHT] = SDL_SCANCODE_S;
  default_keys[v_keys::NINE]  = SDL_SCANCODE_D;
  default_keys[v_keys::E]     = SDL_SCANCODE_F;
  
  default_keys[v_keys::A]     = SDL_SCANCODE_Z;
  default_keys[v_keys::ZERO]  = SDL_SCANCODE_X;
  default_keys[v_keys::B]     = SDL_SCANCODE_C;
  default_keys[v_keys::F]     = SDL_SCANCODE_V;

  return default_keys;
}
