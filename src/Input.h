#pragma once

#include <SDL.h>
#include <map>

const uint8_t KEY_COUNT = 16;

/*
  -Virtual key map-

  123C
  456D
  789E
  A0BF

  -Physical key map-

  1234
  qwer
  asdf
  zxcv
*/



enum v_keys {
  ZERO = 0,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  
  A,
  B,
  C,
  D,
  E,
  F
};

class input {
 private:
  bool keys[KEY_COUNT];
  std::map<uint8_t, SDL_Scancode> bound_keys;

 public:

  input();
  ~input();

  void bind_default();
  
  void frame_reset();
  
  void keydown_event(SDL_Event& e);
  //void keyup_event(SDL_Event& e);

  bool is_keydown(uint8_t key);
  bool is_keyup(uint8_t key);
  
};
