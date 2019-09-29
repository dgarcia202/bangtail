#include <iostream>

#include "../src/include/bangtail.h"

class MovementBehavior : public Behavior
{
private:
  Sprite2D *sprite = nullptr;
  Vector2 speed = {55.0, 41.0};
  Input *input = nullptr;

public:
  MovementBehavior(ObjectKey key): Behavior(key) {}
  void behaviorInit();
  void behaviorUpdate(float);
};