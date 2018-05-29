#pragma once

#include <SDL.h>

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
  one = 0,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  zero,
  a,
  b,
  c,
  d,
  e,
  f  
};

class input {
 private:
  bool keys[KEY_COUNT];
  
 public:

  input();
  ~input();
  
  void keydown_event(SDL_Event& e);
  void keyup_event(SDL_Event& e);

  bool is_keydown();
  bool is_keyup();
  
};
