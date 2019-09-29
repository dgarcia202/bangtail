#ifndef _BEHAVIOR_HPP
#define _BEHAVIOR_HPP

#include "GameObject.hpp"

class Behavior : public GameObject
{
public:
  Behavior(ObjectKey key) : GameObject(key) {}
  void init();
  void update(float);
  void destroy();

protected:
  virtual void behaviorInit();
  virtual void behaviorUpdate(float) = 0;
  virtual void behaviorDestroy();
};

#endif // _BEHAVIOR_HPP