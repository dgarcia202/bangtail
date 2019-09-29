#ifndef _COLLIDER_HPP
#define _COLLIDER_HPP

#include "GameObject.hpp"

class Collider : public GameObject
{
public:
  Collider(ObjectKey key) : GameObject(key) {}
  bool collidesWith(GameObject *);

  virtual void render();
};

#endif // _COLLIDER_HPP