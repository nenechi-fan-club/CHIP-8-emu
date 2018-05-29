#include "input.h"

input::input() {

}

input::~input() {

}

void input::keydown_event(SDL_Event& e) {
  /*  auto sc = e.key.keysym.scancode;
  if (sc == SDL_SCANCODE_1)
    ;
  */

}

void input::keyup_event(SDL_Event& e) {

}

bool input::is_keydown(v_keys key ) {
  return keys[key];
}

bool input::is_keyup(v_keys key) {
  if (keys[key])
    return false;
  return true;
}
