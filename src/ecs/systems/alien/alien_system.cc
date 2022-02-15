#include "alien_system.h"

#include <SDL_image.h>

AlienSystem::AlienSystem() {
  colliders_ = new Collider[kMaxSize_];
  physics_ = new Physics[kMaxSize_];
  sprites_ = new Sprite[kMaxSize_];
  transforms_ = new Transform[kMaxSize_];
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
  Sprite sprite;
  sprite.texture = spaceInvader;

  int count = 0;
  int spawnX = startX;
  int spawnY = startY;
  for (int i = 0; i < kMaxSize_; i++) {
    Transform transform;
    transform.position.x = static_cast<float>(spawnX);
    transform.position.y = static_cast<float>(spawnY);
    transforms_[i] = transform;

    Collider collider;
    collider.rect.w = alienWidth;
    collider.rect.h = alienHeight;
    colliders_[i] = collider;

    Physics physics;
    physics.speed = 0.1f;
    physics_[i] = physics;

    sprites_[i] = sprite;

    size_ = i;

    ++count;
    spawnX += alienWidth;
    if (count % columns == 0) {
      spawnX = startX;
      spawnY += alienHeight;
    }
  }
}

void AlienSystem::terminate() {
  for (int i = 0; i <= size_; i++) {
    SDL_DestroyTexture(sprites_[i].texture);
    sprites_[i].texture = nullptr;
  }
}

void AlienSystem::input(SDL_Event event) {
  for (int i = 0; i <= size_; i++) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
      Vector2 v;
      switch (event.key.keysym.sym) {
        case SDLK_LEFT:
          v.x = -physics_[i].speed;
          v.y = 0.0;
          break;
        case SDLK_RIGHT:
          v.x = physics_[i].speed;
          v.y = 0.0;
          break;
        case SDLK_UP:
          v.x = 0.0;
          v.y = -physics_[i].speed;
          break;
        case SDLK_DOWN:
          v.x = 0.0;
          v.y = physics_[i].speed;
          break;
      }
      physics_[i].acceleration = v;
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
      physics_[i].acceleration = Vector2();
    }
  }
}

void AlienSystem::updatePosition() {
  for (int i = 0; i <= size_; i++) {
    physics_[i].velocity += physics_[i].acceleration;
    transforms_[i].position += physics_[i].velocity;

    if (transforms_[i].position.y < 0) {
      transforms_[i].position.y = 720;
    } else if (transforms_[i].position.y > 720) {
      transforms_[i].position.y = 0;
    }

    if (transforms_[i].position.x < 0) {
      transforms_[i].position.x = 1280;
    } else if (transforms_[i].position.x > 1280) {
      transforms_[i].position.x = 0;
    }

    colliders_[i].update(transforms_[i].position);
  }
}

void AlienSystem::renderSprite(SDL_Renderer* renderer, float delay) {
  for (int i = 0; i <= size_; i++) {
    SDL_Rect rect;

    if (delay > 0) {
      Vector2 velocity = physics_[i].velocity * delay;
      Vector2 position = transforms_[i].position + velocity;

      SDL_Point point = Utils::topLeftPoint(position, colliders_[i].rect);

      rect = {point.x, point.y, colliders_[i].rect.w, colliders_[i].rect.h};
    } else {
      rect = colliders_[i].rect;
    }

    SDL_RenderCopy(renderer, sprites_[i].texture, nullptr, &rect);
  }
}

void AlienSystem::renderCollider(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  for (int i = 0; i <= size_; i++) {
    SDL_RenderDrawRect(renderer, &colliders_[i].rect);
  }
}
