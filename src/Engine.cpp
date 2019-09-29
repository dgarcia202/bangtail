#include "Engine.hpp"

Engine::Engine()
{
  quit = false;
  gameController = nullptr;
}

Engine *Engine::init()
{
  Engine *engineptr = new Engine();
  if (engineptr->internalInit())
  {
    return engineptr;
  }

  return nullptr;
}

int Engine::run()
{
  SDL_Log("Starting app...\n");
  if (currentScene == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No initial scene defined");
    quit = true;
  }

  if (!currentScene->isInitialized())
  {
    currentScene->init();
  }

  while (!quit)
  {
    handleEvents();

    Uint32 ticks = SDL_GetTicks();
    Uint32 ellapsed = ticks - lastTick;
    if ((ellapsed) >= (1000 / TARGET_FRAME_RATE))
    {
      lastTick = ticks;
      update(static_cast<float>(ellapsed));
      render();
    }
  }
  cleanup();

  SDL_Log("Exiting...\n");
  return 0;
}

bool Engine::internalInit()
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  if (SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt") < 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize controllers! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  int numJoysticks = SDL_NumJoysticks();

#ifdef DEBUG
  int numControllers = 0;
  for (int i = 0; i < numJoysticks; ++i)
  {
    const char *name;
    const char *description;
    char guid[64];

    SDL_JoystickGetGUIDString(SDL_JoystickGetDeviceGUID(i), guid, sizeof(guid));
    if (SDL_IsGameController(i))
    {
      numControllers++;
      name = SDL_GameControllerNameForIndex(i);
      description = "Controller";
    }
    else
    {
      name = SDL_JoystickNameForIndex(i);
      description = "Joystick";
    }
    SDL_Log("%s %d: %s (guid %s)\n", description, i, name ? name : "Unknown", guid);
  }
  SDL_Log("There are %d game controller(s) attached (%d joystick(s))\n", numControllers, numJoysticks);
#endif // DEBUG

  // Initizalize game controller if present
  for (int i = 0; i < numJoysticks; ++i)
  {
    if (SDL_IsGameController(i))
    {
      gameController = SDL_GameControllerOpen(i);
#ifdef DEBUG
      SDL_Log("Found game controller at joystick index %d\n", i);
#endif // DEBUG
      break;
    }
  }

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    SDL_Quit();
    return false;
  }

  //Create window
  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create a renderer! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  Assets::setRenderer(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  return true;
}

void Engine::cleanup()
{

#ifdef DEBUG
  SDL_Log("cleaning up...\n");
#endif

  if (gameController)
  {
#ifdef DEBUG
    SDL_Log("Closing game controller\n");
#endif // DEBUG
    SDL_GameControllerClose(gameController);
    gameController = nullptr;
  }

  if (renderer)
  {
#ifdef DEBUG
    SDL_Log("Destroying renderer\n");
#endif // DEBUG
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }

  if (window)
  {
#ifdef DEBUG
    SDL_Log("Destroying window\n");
#endif // DEBUG
    SDL_DestroyWindow(window);
    window = nullptr;
  }

  Assets::freeResources();
  IMG_Quit();
  SDL_Quit();
}

void Engine::handleEvents()
{
  SDL_Event e;
  while (SDL_PollEvent(&e) && !quit)
  {
    if (e.type == SDL_QUIT)
    {
      quit = true;
    }

    input.handleEvent(&e);
  }
}

void Engine::update(float ellapsedMillis)
{
  currentScene->update(ellapsedMillis);
}

void Engine::render()
{
  SDL_RenderClear(renderer);

  currentScene->render();

  SDL_RenderPresent(renderer);
}

void Engine::addScene(Scene *scene)
{
  scene->setRenderer(renderer);
  scene->setInput(&input);
  scenes.push_back(scene);
  if (scenes.size() == 1)
  {
    currentScene = scene;
  }  
}