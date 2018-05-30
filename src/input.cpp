#include "input.h"

input::input() {
  for (auto &i : key_status) {
    i = false;
  }
  bind_default();
}

input::~input() {}

/*void input::frame_reset() {
  for (int i = 0; i < KEY_COUNT; i++) {
    keys[i] = false;
  }
}*/

void input::keydown_event(const SDL_Event& e) {
  set_key_status(e.key.keysym.scancode, true);
}

void input::keyup_event(const SDL_Event& e) {
  set_key_status(e.key.keysym.scancode, false);
}

void input::set_key_status(SDL_Scancode scancode, bool status) {
  for (const auto &key : keys) {
    if (key.second == scancode) {
      key_status[key.first] = status;
      printf("INPUT EVENT ADDED; %d, %d, %d \n", key.first, key.second, key_status[key.first]);
    }
  }

}

<<<<<<< HEAD
bool input::is_keydown(uint8_t key) const {
  if (key > 15) {
=======
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
>>>>>>> 8642ada80380561021c12411a9d5d44c7f2c47da
    printf("Error! Key > 16\n");
    return false;
  }
  else {
<<<<<<< HEAD
    printf("%d\n", key);
    return key_status[key];
=======
    return keys[key];
>>>>>>> 8642ada80380561021c12411a9d5d44c7f2c47da
  }
  //return (key > 15) ? false : key_status[key];
}

<<<<<<< HEAD
bool input::is_keydown() const {
  for (const auto& key : keys) {
    if (key_status[key.first]) return true;
=======
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
>>>>>>> 8642ada80380561021c12411a9d5d44c7f2c47da
  }
  return false;
}

<<<<<<< HEAD
bool input::is_keyup(uint8_t key) const {
  return !is_keydown(key);
}

void input::bind_default() {
  keys[v_keys::ONE]   = SDL_SCANCODE_1;
  keys[v_keys::TWO]   = SDL_SCANCODE_2;
  keys[v_keys::THREE] = SDL_SCANCODE_3;
  keys[v_keys::C]     = SDL_SCANCODE_4;
  
  keys[v_keys::FOUR]  = SDL_SCANCODE_Q;
  keys[v_keys::FIVE]  = SDL_SCANCODE_W;
  keys[v_keys::SIX]   = SDL_SCANCODE_E;
  keys[v_keys::D]     = SDL_SCANCODE_R;
  
  keys[v_keys::SEVEN] = SDL_SCANCODE_A;
  keys[v_keys::EIGHT] = SDL_SCANCODE_S;
  keys[v_keys::NINE]  = SDL_SCANCODE_D;
  keys[v_keys::E]     = SDL_SCANCODE_F;
  
  keys[v_keys::A]     = SDL_SCANCODE_Z;
  keys[v_keys::ZERO]  = SDL_SCANCODE_X;
  keys[v_keys::B]     = SDL_SCANCODE_C;
  keys[v_keys::F]     = SDL_SCANCODE_V;
=======


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
>>>>>>> 8642ada80380561021c12411a9d5d44c7f2c47da
}
