#include "Behavior.hpp"

void Behavior::init()
{
  GameObject::init();
  behaviorInit();
}

void Behavior::update(float ellapsedMillis)
{
  behaviorUpdate(ellapsedMillis);
  GameObject::update(ellapsedMillis);
}

void Behavior::destroy()
{
  behaviorDestroy();
  GameObject::destroy();
}

void Behavior::behaviorInit()
{
}

void Behavior::behaviorDestroy()
{
}
