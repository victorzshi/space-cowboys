#include "game.h"

Game::Game() : isRunning_(true) {
  window_ = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, kScreenWidth,
                             kScreenHeight, SDL_WINDOW_SHOWN);

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    render(lag / kTicksPerUpdate);

    if (isSmokeTest && current > kSmokeTestDuration) {
      isRunning_ = false;
    }
  }
}

void Game::input() {
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      isRunning_ = false;
    }

    // TODO(Victor): Process input for entities.
  }
}

void Game::update() {
  // TODO(Victor): Update entities.
}

void Game::render(double delay) {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);

  (void)delay;
  // TODO(Victor): Render entities.

  SDL_RenderPresent(renderer_);
}
