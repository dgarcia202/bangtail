#ifndef _ASSETS_HPP
#define _ASSETS_HPP

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "bangtail_std.h"

class Assets
{
public:
  static void setRenderer(SDL_Renderer *renderer_p) { renderer = renderer_p; }
  static void loadTexture(TextureKey, std::string);
  static SDL_Texture *getTexture(TextureKey);
  static void freeResources();

private:
  static SDL_Renderer *renderer;
  static TextureCollection textures;
};

#endif // _ASSETS_HPP