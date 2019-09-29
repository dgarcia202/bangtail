#include "test.hpp"

void loadAssets();

int main(int argc, char *argv[])
{
  Logger log;
  Engine *e = Engine::init();
  loadAssets();
  Collider coll("sprite_collider");
  coll.setSize(81, 87);

  Sprite2D fruits("fruits_sprite");
  fruits.setTexture(Assets::getTexture("fruits"));
  fruits.setSize(81, 87);
  fruits.setPosition(100, 100);
  fruits.setCurrentFrame(0);
  fruits.add(&coll);

  MovementBehavior movement("movement_script");

  Scene main("main_scene");
  main.add(&fruits);
  main.add(&movement);

  e->addScene(&main);
  e->run();

  Engine::dispose(e);
  return 0;
}

void loadAssets()
{
  Assets::loadTexture("fruits", "assets/fruits.png");
}

void MovementBehavior::behaviorInit()
{
  sprite = static_cast<Sprite2D *>(find("fruits_sprite"));
  input = getInput();
}

void MovementBehavior::behaviorUpdate(float ellapsedMillis)
{
  static int accum = 0;
  int frame = sprite->getCurrentFrame();
  Vector2 position = sprite->getPosition();
  float factor = ellapsedMillis / 1000.0;

  sprite->setPosition(position.x + (speed.x * factor), position.y + (speed.y * factor));
  accum += ellapsedMillis;

  if (input->isKeyPressed(SDLK_LCTRL) && accum > 250)
  {
    sprite->setCurrentFrame(frame < 3 ? ++frame : 0);
    accum = 0;
  }
}