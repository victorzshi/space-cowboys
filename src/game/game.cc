#include "game.h"

Game::Game() : isRunning_(true) {
  window_ = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, kScreenWidth,
                             kScreenHeight, SDL_WINDOW_SHOWN);

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  entities_.initialize(kScreenWidth, kScreenHeight);
}

bool Game::initialize() { return SDL_Init(SDL_INIT_VIDEO) == 0; }

void Game::terminate() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
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
      entities_.update();
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
