#include "Sprite2D.hpp"

void Sprite2D::setTexture(SDL_Texture *texture)
{
  this->texture = texture;
}

void Sprite2D::init()
{
  if (disposition == DISPOSITION_GRID) // TODO: implement custom disposition
  {
    int textureWidth, textureHeight;
    if (SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight) == -1)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to query the texture in 2DSprite with key: %s", getKey().c_str());
      return;
    }

    Uint32 r, c;
    SDL_Rect dimensions = {getPosition().x, getPosition().y, getSize().x, getSize().y};
    for (r = 0; r < (textureHeight / dimensions.h); ++r)
    {
      for (c = 0; c < (textureWidth / dimensions.w); ++c)
      {
        clips.push_back({(c * dimensions.w), (r * dimensions.h), dimensions.w, dimensions.h});
      }
    }
  }

  GameObject::init();
}

void Sprite2D::update(float ellapsedMillis)
{
  GameObject::update(ellapsedMillis);
}

void Sprite2D::render()
{
  Vector2 pos = getAbsolutePosition();
  Vector2 size = getSize();
  SDL_Rect orgn = clips[currentFrame];
  SDL_Rect dim = {pos.x, pos.y, size.x, size.y};
  SDL_RenderCopyEx(getRenderer(), texture, &orgn, &dim, 0.0, NULL, SDL_FLIP_NONE);

  GameObject::render();
}