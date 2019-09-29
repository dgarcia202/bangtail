#include "Assets.hpp"

SDL_Renderer *Assets::renderer = nullptr;
TextureCollection Assets::textures;

void Assets::loadTexture(TextureKey key, std::string path)
{
   if (renderer == nullptr)
   {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Coundn't manage assets with an uninitialized engine");
      return;
   }

   SDL_Surface *loadedSurface = IMG_Load(path.c_str());
   if (loadedSurface == nullptr)
   {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Coundn't load surface from: %s\n", path);
      return;
   }

   SDL_Texture *t;
   t = SDL_CreateTextureFromSurface(renderer, loadedSurface);
   if (t == nullptr)
   {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed creating texture from loaded: %s\n", path);
      return;
   }

   textures[key] = t;
   SDL_FreeSurface(loadedSurface);
}

SDL_Texture *Assets::getTexture(TextureKey key)
{
   return textures[key];
}

void Assets::freeResources()
{
   TextureCollection::iterator it;
   for (it = textures.begin(); it != textures.end(); ++it)
   {
      SDL_DestroyTexture(it->second);
   }
}