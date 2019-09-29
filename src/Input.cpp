#include "Input.hpp"

void Input::handleEvent(SDL_Event *e)
{
  if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
  {
    keymap.emplace(e->key.keysym.sym);
  } 
  else if (e->type == SDL_KEYUP && e->key.repeat == 0)
  {
    keymap.erase(e->key.keysym.sym);
  }
}

bool Input::isKeyPressed(SDL_Keycode key)
{
  return keymap.find(key) != keymap.end();
}