#ifndef _GAME_OBJECT_HPP
#define _GAME_OBJECT_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "Input.hpp"
#include "bangtail_std.h"

class GameObject
{
public:
  GameObject(ObjectKey key) { this->key = key; }

  void add(GameObject *);
  virtual void init();
  virtual void update(float);
  virtual void render();
  virtual void destroy();

  void setKey(const ObjectKey key) { this->key = key; }
  ObjectKey getKey() { return key; }
  void setPosition(float x, float y)
  {
    position.x = x;
    position.y = y;
  }
  void setPositionX(float x) { position.x = x; }
  void setPositionY(float y) { position.y = y; };
  void setSize(float w, float h)
  {
    size.x = w;
    size.y = h;
  }
  void setWidth(float w) { size.x = w; }
  void setHeight(float h) { size.y = h; }
  Vector2 getPosition() { return position; }
  Vector2 getAbsolutePosition();
  Vector2 getSize() { return size; }
  void setRenderer(SDL_Renderer *);
  SDL_Renderer *getRenderer() { return renderer; }
  void setInput(Input *);
  Input *getInput() { return input; }
  bool isInitialized() { return initialized; }
  void setParent(GameObject *obj) { parent = obj; }
  GameObject *getParent() { return parent; }
  GameObject *find(ObjectKey);
  GameObject *findChild(ObjectKey);

protected:
  Logger log;

  void saveDrawColor();
  void restoreDrawColor() { SDL_SetRenderDrawColor(renderer, r, g, b, a); }

private:
  ObjectKey key;
  ObjectCollection objects;
  bool initialized = false;
  GameObject *parent = nullptr;
  SDL_Renderer *renderer = nullptr;
  Input *input = nullptr;
  Vector2 position = Vector2::zero();
  Vector2 size = Vector2::zero();
  Uint8 r = 0, g = 0, b = 0, a = 0;
};

#endif // _GAME_OBJECT_HPP