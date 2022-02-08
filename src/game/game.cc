#include "game.h"

#include "tank/tank.h"

Game::Game() : isRunning_(true) {
  window_ = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, kScreenWidth,
                             kScreenHeight, SDL_WINDOW_SHOWN);

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

bool Game::initialize() {
  for (int i = 0; i < kMaxObjects; i++) {
    objects[i] = nullptr;
  }

  GameObject* tank = Tank::createTank();
  tank->position = Vector2(kScreenWidth / 2.0, kScreenHeight / 2.0);
  objects[0] = tank;

  return SDL_Init(SDL_INIT_VIDEO) == 0;
}

void Game::start(bool isSmokeTest) {
  double previous = static_cast<double>(SDL_GetTicks64());
  double lag = 0.0;

  while (isRunning_) {
    double current = static_cast<double>(SDL_GetTicks64());
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;
    input();

    while (lag >= kTicksPerUpdate) {
      update();
      lag -= kTicksPerUpdate;
    }

    render();

    if (isSmokeTest && current > kSmokeTestDuration) {
      isRunning_ = false;
    }
  }
}

void Game::stop() {
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Game::input() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      isRunning_ = false;
    }

    for (int i = 0; i < kMaxObjects; i++) {
      if (objects[i] != nullptr) {
        objects[i]->processInput(event);
      }
    }
  }
}

void Game::update() {
  for (int i = 0; i < kMaxObjects; i++) {
    if (objects[i] != nullptr) {
      objects[i]->update(*this);
    }
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);

  for (int i = 0; i < kMaxObjects; i++) {
    if (objects[i] != nullptr) {
      objects[i]->render(renderer_);
    }
  }

  SDL_RenderPresent(renderer_);
}
