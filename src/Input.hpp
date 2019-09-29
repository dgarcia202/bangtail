#ifndef _INPUT_HPP
#define _INPUT_HPP

#include <SDL2/SDL.h>

#include "bangtail_std.h"

class Input
{
public:
  void handleEvent(SDL_Event*);
  bool isKeyPressed(SDL_Keycode);

private:
  Logger log;
  KeyMap keymap;  
};

#endif // _INPUT_HPP
