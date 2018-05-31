#pragma once

#include <array>
#include <map>

#include <SDL.h>

//const uint8_t KEY_COUNT = 16;

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
  F,
  KEY_COUNT
};

class input {
public:
  input();
  ~input();

public:
  void keydown_event(const SDL_Event& e);
  void keyup_event(const SDL_Event& e);
  
  bool is_keydown(uint8_t key) const; //checks if key with key id is pressed
  bool is_keydown() const;            //check if any key is pressed
  bool is_keyup(uint8_t key) const;

  void logging(bool option);
  
private:
  void bind_default();
  void set_key_status(SDL_Scancode code, bool status);

private:
  std::array<bool, KEY_COUNT> key_status;
  std::map<uint8_t, SDL_Scancode> keys;

  bool log_inputs = false;   // Logging off by default

  //void frame_reset();
};
