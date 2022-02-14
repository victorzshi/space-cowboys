#include "game.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "services/locator.h"

Game::Game() : isRunning_(true) {
  window_ = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, kScreenWidth,
                             kScreenHeight, SDL_WINDOW_SHOWN);

  renderer_ = SDL_CreateRenderer(
  // window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   window_, -1, SDL_RENDERER_ACCELERATED);
}

bool Game::initialize() {
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    Locator::logger().print("SDL could not initialize!");
    success = false;
  }

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    Locator::logger().print("SDL_image could not initialize!");
    success = false;
  }

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    Locator::logger().print("SDL_ttf could not initialize!");
    success = false;
  }

  // Initialize entities
  entities_.initialize(kScreenWidth, kScreenHeight, renderer_);

  return success;
}

void Game::terminate() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  TTF_Quit();
  SDL_Quit();
}

void Game::run(bool isSmokeTest) {
  double previous = static_cast<double>(SDL_GetTicks64());
  double lag = 0.0;

  SDL_Event event;

  while (isRunning_) {
    double current = static_cast<double>(SDL_GetTicks64());
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;

    // Process input
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        isRunning_ = false;
      }

      entities_.input(event);
    }

    // Update state
    while (lag >= kTicksPerUpdate) {
      entities_.update(renderer_);
      lag -= kTicksPerUpdate;
    }

    // Render graphics
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);

    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);

    entities_.render(renderer_, lag / kTicksPerUpdate);

    SDL_RenderPresent(renderer_);

    // Handle testing
    if (isSmokeTest && current > kSmokeTestDuration) {
      isRunning_ = false;
    }
  }
}
