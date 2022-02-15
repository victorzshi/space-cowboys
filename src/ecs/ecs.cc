#include "ecs.h"

void ECS::initialize(int screenWidth, int screenHeight,
                     SDL_Renderer* renderer) {
  alienSystem.initialize(screenWidth, screenHeight, renderer);
}

void ECS::terminate() { alienSystem.terminate(); }

void ECS::input(SDL_Event event) { alienSystem.input(event); }

void ECS::update() { alienSystem.updatePosition(); }

void ECS::render(SDL_Renderer* renderer, float delay) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  alienSystem.renderSprite(renderer, delay);
  alienSystem.renderCollider(renderer);
}
