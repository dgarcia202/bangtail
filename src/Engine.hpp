#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "bangtail_std.h"
#include "GameObject.hpp"
#include "Input.hpp"
#include "Assets.hpp"

class Engine
{
public:
  Engine();
  int run();
  void addScene(Scene *scene);

  static Engine *init();
  static void dispose(Engine *e) { delete e; }
  
private:
  Input input;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_GameController *gameController;
  bool quit;
  Uint32 lastTick;
  SceneCollection scenes;
  Scene *currentScene;

  bool internalInit();
  void cleanup();
  void handleEvents();
  void update(float);
  void render();
};

#endif // _ENGINE_HPP