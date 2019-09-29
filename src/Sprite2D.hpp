#ifndef _SPRITE2D_HPP
#define _SPRITE2D_HPP

#include "SDL2/SDL.h"
#include "GameObject.hpp"

typedef std::vector<SDL_Rect> clips_t;

typedef enum
{
  DISPOSITION_GRID,
  DISPOSITION_CUSTOM
} FrameDisposition;

class Sprite2D : public GameObject
{
public:
  Sprite2D(ObjectKey key) : GameObject(key) {}
  void setTexture(SDL_Texture *);
  SDL_Texture *getTexture() { return texture; }
  void setFrameDisposition(FrameDisposition disposition) { this->disposition = disposition; }
  FrameDisposition getFrameDisposition() { return disposition; }
  SDL_Point getFramesize() { return SDL_Point{getSize().x, getSize().y}; }
  void setCurrentFrame(int index) { currentFrame = index; }
  Uint32 getCurrentFrame() { return currentFrame; }

  virtual void init();
  virtual void update(float);
  virtual void render();

private:
  SDL_Texture *texture;
  FrameDisposition disposition = DISPOSITION_GRID;
  clips_t clips;
  Uint32 currentFrame = 0;
  Uint32 totalFrames = 0;
};

#endif // _SPRITE2D_HPP