#include "Collider.hpp"

void Collider::render()
{
#ifdef DEBUG
  saveDrawColor();
  SDL_SetRenderDrawColor(getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
  Vector2 absolute = getAbsolutePosition();
  SDL_Rect rect = {
      absolute.x, absolute.y,
      getSize().x, getSize().y};

  SDL_RenderDrawRect(getRenderer(), &rect);
  restoreDrawColor();
#endif // DEBUG
}

bool Collider::collidesWith(GameObject *other)
{
  return false;
}