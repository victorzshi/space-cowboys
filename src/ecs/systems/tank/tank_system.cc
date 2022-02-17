#include "tank_system.h"

#include <SDL_image.h>

TankSystem::TankSystem() {
  collider_ = new Collider[kMaxSize_];
  physics_ = new Physics[kMaxSize_];
  sprite_ = new Sprite[kMaxSize_];
  transform_ = new Transform[kMaxSize_];
}

void TankSystem::initialize(int screenWidth, int screenHeight,
                            SDL_Renderer* renderer) {
  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = IMG_Load("../../data/images/tank.png");
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  for (int i = 0; i < kMaxSize_; i++) {
    transform_[i].position.x = static_cast<float>(screenWidth / 2);
    transform_[i].position.y = static_cast<float>(screenHeight / 2);

    collider_[i].rect.w = 50;
    collider_[i].rect.h = 50;

    sprite_[i].texture = texture;

    size_ = i + 1;
  }
}

void TankSystem::terminate() {
  for (int i = 0; i < size_; i++) {
    SDL_DestroyTexture(sprite_[i].texture);
    sprite_[i].texture = nullptr;
  }
}

void TankSystem::inputDirection(SDL_Event event) {
  for (int i = 0; i < size_; i++) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          //physics_[i].acceleration.x = -physics_[i].speed;
          break;
        case SDLK_RIGHT:
          //physics_[i].acceleration.x = physics_[i].speed;
          break;
      }
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
      physics_[i].acceleration = Vector2();
      physics_[i].velocity = Vector2();
    }
  }
}

void TankSystem::updatePosition() {
  for (int i = 0; i < size_; i++) {
    physics_[i].velocity += physics_[i].acceleration;
    transform_[i].position += physics_[i].velocity;
    collider_[i].update(transform_[i].position);
  }

  if (isOutOfBounds()) {
    for (int i = 0; i <= size_; i++) {
      transform_[i].position -= physics_[i].velocity;
      collider_[i].update(transform_[i].position);
    }
  }
}

void TankSystem::renderSprite(SDL_Renderer* renderer, float delay) {
  for (int i = 0; i < size_; i++) {
    SDL_Rect rect;

    if (delay > 0) {
      Vector2 velocity = physics_[i].velocity * delay;
      Vector2 position = transform_[i].position + velocity;

      SDL_Point point = Utils::topLeftPoint(position, collider_[i].rect);

      rect = {point.x, point.y, collider_[i].rect.w, collider_[i].rect.h};
    } else {
      rect = collider_[i].rect;
    }

    SDL_RenderCopy(renderer, sprite_[i].texture, nullptr, &rect);
  }
}

void TankSystem::renderCollider(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  for (int i = 0; i < size_; i++) {
    SDL_RenderDrawRect(renderer, &collider_[i].rect);
  }
}

bool TankSystem::isOutOfBounds() {
  for (int i = 0; i < size_; i++) {
    // TODO(Victor): Remove hardcoded screen dimensions.
    if (transform_[i].position.x < 0 || transform_[i].position.x > 1280) {
      return true;
    }
  }
  return false;
}
