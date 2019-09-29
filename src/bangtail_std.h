#ifndef _BANGTAIL_STD_H
#define _BANGTAIL_STD_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

#include "SDL2/SDL.h"

#define WINDOW_TITLE "Bangtail"
#define KEYMAP_SIZE 2560

class GameObject;

typedef GameObject Scene;
typedef std::vector<GameObject *> SceneCollection;
typedef std::vector<GameObject *> ObjectCollection;
typedef std::map<std::string, SDL_Texture *> TextureCollection;
typedef std::unordered_set<SDL_Keycode> KeyMap;

typedef std::string ObjectKey;
typedef std::string TextureKey;

typedef struct Vector2
{
  float x, y;
  static struct Vector2 zero() { return {0, 0}; }
  static struct Vector2 sum(struct Vector2 a, struct Vector2 b) { return {a.x + b.x, a.y + b.y}; }
} Vector2;

const int TARGET_FRAME_RATE = 60;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int UP_KEY = 0;
const int DOWN_KEY = 1;
const int RIGHT_KEY = 2;
const int LEFT_KEY = 3;
const int FIRE_KEY = 4;

class Logger
{
public:
  template <typename T, typename... Args>
  void debug(T first, Args... args)
  {
    std::cout << "DEBUG: " << first;
    log(args...);
  }

  template <typename T, typename... Args>
  void info(T first, Args... args)
  {
    std::cout << "INFO: " << first;
    log(args...);
  }

  template <typename T, typename... Args>
  void warn(T first, Args... args)
  {
    std::cout << "WARN: " << first;
    log(args...);
  }

  template <typename T, typename... Args>
  void error(T first, Args... args)
  {
    std::cout << "ERROR: " << first;
    log(args...);
  }

private:
  template <typename T, typename... Args>
  void log(T first, Args... args)
  {
    std::cout << first;
    log(args...);
  }

  void log()
  {
    std::cout << std::endl;
  }
};

#endif // _BANGTAIL_STD_H