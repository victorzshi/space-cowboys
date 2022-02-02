#include "game.hpp"

Game::Game() {
  window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH,
                            m_SCREEN_HEIGHT, 0);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}

bool Game::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  } else {
    return true;
  }
}

void Game::start() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  SDL_Delay(m_STAY_ALIVE);
}

void Game::stop() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
