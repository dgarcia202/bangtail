#include "GameObject.hpp"

void GameObject::init()
{
#ifdef DEBUG
  SDL_Log("Initializing object %s\n", getKey().c_str());
#endif // DEBUG
  ObjectCollection::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
  {
    (*it)->init();
  }

  initialized = true;
}

void GameObject::update(float ellapsedMillis)
{
  ObjectCollection::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
  {
    (*it)->update(ellapsedMillis);
  }
}

void GameObject::render()
{
  ObjectCollection::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
  {
    (*it)->render();
  }
}

void GameObject::destroy()
{
#ifdef DEBUG
  SDL_Log("Destroying object %s\n", getKey().c_str());
#endif // DEBUG
  ObjectCollection::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
  {
    (*it)->destroy();
  }
}

void GameObject::add(GameObject *object)
{
  objects.push_back(object);
  object->setParent(this);
}

void GameObject::setRenderer(SDL_Renderer *renderer)
{
  this->renderer = renderer;
  ObjectCollection::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
  {
    (*it)->setRenderer(renderer);
  }
}

void GameObject::setInput(Input *input)
{
  this->input = input;
  ObjectCollection::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
  {
    (*it)->setInput(input);
  }
}

GameObject *GameObject::find(ObjectKey key)
{
  GameObject *root = this;
  while (root->getParent() != nullptr)
  {
    root = root->getParent();
  }

  return root->findChild(key);
}

GameObject *GameObject::findChild(ObjectKey key)
{
  ObjectCollection::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
  {
    if ((*it)->getKey().compare(key) == 0)
    {
      return *it;
    }

    GameObject *candidate = (*it)->findChild(key);
    if (candidate != nullptr)
    {
      return candidate;
    }
  }

  return nullptr;
}

Vector2 GameObject::getAbsolutePosition()
{
  Vector2 base = getParent() != nullptr ? getParent()->getPosition() : Vector2::zero();

  return Vector2::sum(base, position);
}

void GameObject::saveDrawColor()
{
  Uint8 r, g, b, a;
  if (SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a) == 0)
  {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
}