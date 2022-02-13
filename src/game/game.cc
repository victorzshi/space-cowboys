#include "game.h"

#include <assert.h>

#include "systems/square.h"

Game::Game() : isRunning_(true), totalEntities_(0) {
  window_ = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, kScreenWidth,
                             kScreenHeight, SDL_WINDOW_SHOWN);

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  transforms_ = new Transform[kMaxEntities];
  physics_ = new Physics[kMaxEntities];

  int entity = createEntity();
  addTransform(entity, {Vec2(20.0, 20.0)});

  entity = createEntity();
  addTransform(entity, {Vec2(20.0, kScreenHeight - 20.0)});

  entity = createEntity();
  addTransform(entity, {Vec2(kScreenWidth - 20.0, 20.0)});

  entity = createEntity();
  addTransform(entity, {Vec2(kScreenWidth - 20.0, kScreenHeight - 20.0)});
}

bool Game::initialize() { return SDL_Init(SDL_INIT_VIDEO) == 0; }

void Game::terminate() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

SDL_Renderer* Game::renderer() { return renderer_; }

int Game::totalEntities() { return totalEntities_; }

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

    Square::inputPositions(*this, event, physics_);
  }
}

void Game::update() { Square::updatePositions(*this, transforms_, physics_); }

void Game::render(double delay) {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);

  Square::renderPositions(*this, delay, transforms_, physics_);

  SDL_RenderPresent(renderer_);
}

int Game::createEntity() {
  assert(totalEntities_ < kMaxEntities);

  ++totalEntities_;
  return totalEntities_ - 1;
}

void Game::addTransform(int entity, Transform transform) {
  transforms_[entity] = transform;
}
