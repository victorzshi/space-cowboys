#include "alien_system.h"

#include <SDL_image.h>

AlienSystem::AlienSystem() {
  ai_ = new AI[kMaxSize_];
  collider_ = new Collider[kMaxSize_];
  physics_ = new Physics[kMaxSize_];
  sprite_ = new Sprite[kMaxSize_];
  transform_ = new Transform[kMaxSize_];
}

void AlienSystem::initialize(int screenWidth, int screenHeight,
                             SDL_Renderer* renderer) {
  int alienWidth = 50;
  int alienHeight = 50;

  int rows = 5;
  int columns = 11;

  int spawnWidth = columns * alienWidth;
  int spawnHeight = rows * alienHeight;

  int startX = screenWidth / 2 - spawnWidth / 2 + alienWidth / 2;
  int startY = screenHeight / 4 - spawnHeight / 2 + alienHeight / 2;

  // Load space invader image
  SDL_Texture* spaceInvader = nullptr;
  SDL_Surface* loadedSurface = IMG_Load("../../data/space-invader.png");
  spaceInvader = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);

  int spawnX = startX;
  int spawnY = startY;
  for (int i = 0; i < kMaxSize_; i++) {
    transform_[i].position.x = static_cast<float>(spawnX);
    transform_[i].position.y = static_cast<float>(spawnY);

    collider_[i].rect.w = alienWidth;
    collider_[i].rect.h = alienHeight;

    physics_[i].speed = -5.0f;
    physics_[i].velocity.x = physics_[i].speed;

    ai_[i].direction = Direction::kLeft;

    sprite_[i].texture = spaceInvader;

    // Account for 0 index
    size_ = i + 1;

    spawnX += alienWidth;
    if (size_ % columns == 0) {
      spawnX = startX;
      spawnY += alienHeight;
    }
  }
}

void AlienSystem::terminate() {
  for (int i = 0; i < size_; i++) {
    SDL_DestroyTexture(sprite_[i].texture);
    sprite_[i].texture = nullptr;
  }
}

void AlienSystem::updateDirection() {
  // Check all alien positions
  // If any are out of bounds, update ALL directions
  if (isOutOfBounds()) {
    for (int i = 0; i < size_; i++) {
      switch (ai_[i].direction) {
        case Direction::kLeft:
          ai_[i].direction = Direction::kRight;
          physics_[i].velocity.x = physics_[i].speed;
          break;
        case Direction::kRight:
          ai_[i].direction = Direction::kLeft;
          physics_[i].velocity.x = -physics_[i].speed;
          break;
      }
    }
  }


}

void AlienSystem::updatePosition() {
  for (int i = 0; i < size_; i++) {
    transform_[i].position += physics_[i].velocity;
    collider_[i].update(transform_[i].position);
  }
}

void AlienSystem::renderSprite(SDL_Renderer* renderer, float delay) {
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

void AlienSystem::renderCollider(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  for (int i = 0; i < size_; i++) {
    SDL_RenderDrawRect(renderer, &collider_[i].rect);
  }
}

bool AlienSystem::isOutOfBounds() {
  for (int i = 0; i < size_; i++) {
    if (transform_[i].position.x < 0 || transform_[i].position.x > 1280) {
      return true;
    }
  }
  return false;
}
