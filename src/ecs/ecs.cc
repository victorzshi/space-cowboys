#include "ecs.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <assert.h>

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/sprite.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/systems/input_ai/input_ai.h"
#include "ecs/systems/input_player/input_player.h"
#include "ecs/systems/render_collider/render_collider.h"
#include "ecs/systems/render_sprite/render_sprite.h"
#include "ecs/systems/update_aliens/update_aliens.h"
#include "ecs/systems/update_effects/update_effects.h"
#include "ecs/systems/update_hit/update_hit.h"
#include "ecs/systems/update_position/update_position.h"
#include "ecs/systems/update_tanks/update_tanks.h"

ECS::ECS()
    : id_(0),
      isStartScreen_(true),
      renderer_(nullptr),
      viewport_({0, 0, 0, 0}) {
  ai_ = new AI[MAX_ENTITIES];
  collider_ = new Collider[MAX_ENTITIES];
  physics_ = new Physics[MAX_ENTITIES];
  sprite_ = new Sprite[MAX_ENTITIES];
  timer_ = new Timer[MAX_ENTITIES];
  transform_ = new Transform[MAX_ENTITIES];

  active_.ids = new int[MAX_ENTITIES];
  active_.size = 0;

  aliens_.setEngine(this);
  bullets_.setEngine(this);
  explosions_.setEngine(this);
  particles_.setEngine(this);
  tanks_.setEngine(this);
  zappers_.setEngine(this);
}

void ECS::initialize(SDL_Renderer* renderer, SDL_Rect& viewport,
                     const Uint8* keyboard) {
  renderer_ = renderer;
  viewport_ = viewport;
  keyboard_ = keyboard;

  aliens_.initialize();
  bullets_.initialize();
  explosions_.initialize();
  particles_.initialize();
  tanks_.initialize();
  zappers_.initialize();

  initializeStartScreen();
}

void ECS::terminate() {
  for (int i = 0; i < id_; i++) {
    SDL_DestroyTexture(sprite_[i].texture);
    sprite_[i].texture = nullptr;
  }
}

SDL_Renderer* ECS::renderer() { return renderer_; }
SDL_Rect& ECS::viewport() { return viewport_; }
const Uint8* ECS::keyboard() { return keyboard_; }

AI* ECS::ai() { return ai_; }
Collider* ECS::collider() { return collider_; }
Physics* ECS::physics() { return physics_; }
Sprite* ECS::sprite() { return sprite_; }
Timer* ECS::timer() { return timer_; }
Transform* ECS::transform() { return transform_; }

Active& ECS::active() { return active_; }
Aliens& ECS::aliens() { return aliens_; }
Explosions& ECS::explosions() { return explosions_; }
Bullets& ECS::bullets() { return bullets_; }
Particles& ECS::particles() { return particles_; }
Tanks& ECS::tanks() { return tanks_; }
Zappers& ECS::zappers() { return zappers_; }

int ECS::createEntity() {
  assert(id_ < MAX_ENTITIES);
  id_++;
  return id_ - 1;  // Array index starts at 0
}

SDL_Texture* ECS::createTexture(std::string file) {
  std::string relativePath = "../../data/images/" + file;

  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = IMG_Load(relativePath.c_str());
  texture = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);

  return texture;
}

bool ECS::isOutOfBounds(SDL_Rect rect) {
  return rect.x < viewport_.x || rect.x + rect.w > viewport_.w ||
         rect.y < viewport_.y || rect.y + rect.h > viewport_.h;
}

bool ECS::isOutOfBoundsWidth(SDL_Rect rect) {
  return rect.x < viewport_.x || rect.x + rect.w > viewport_.w;
}

bool ECS::isOutOfBoundsTop(SDL_Rect rect) { return rect.y < viewport_.y; }

bool ECS::isOutOfBoundsBottom(SDL_Rect rect) {
  // TODO(Victor): Screen is a bit lower than expected.
  return rect.y + rect.h > viewport_.h + 200;
}

void ECS::updateActive() {
  int index = 0;

  int begin = aliens_.begin();
  int size = aliens_.size();
  for (int i = begin; i < size; i++) {
    active_.ids[index] = i;
    index++;
  }

  begin = bullets_.begin();
  size = bullets_.size();
  for (int i = begin; i < size; i++) {
    active_.ids[index] = i;
    index++;
  }

  begin = explosions_.begin();
  size = explosions_.size();
  for (int i = begin; i < size; i++) {
    active_.ids[index] = i;
    index++;
  }

  begin = particles_.begin();
  size = particles_.size();
  for (int i = begin; i < size; i++) {
    active_.ids[index] = i;
    index++;
  }

  begin = tanks_.begin();
  size = tanks_.size();
  for (int i = begin; i < size; i++) {
    active_.ids[index] = i;
    index++;
  }

  begin = zappers_.begin();
  size = zappers_.size();
  for (int i = begin; i < size; i++) {
    active_.ids[index] = i;
    index++;
  }

  active_.size = index;
}

float ECS::random(float min, float max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(min, max);
  return dis(gen);
}

void ECS::input() {
  if (isStartScreen_) {
    if (keyboard_[SDL_SCANCODE_SPACE]) {
      isStartScreen_ = false;
    }
  } else {
    InputPlayer::input(*this);
    InputAI::input(*this);

    updateActive();
  }
}

void ECS::update() {
  if (!isStartScreen_) {
    UpdatePosition::update(*this);
    UpdateTanks::update(*this);
    UpdateAliens::update(*this);
    UpdateHit::update(*this);
    UpdateEffects::update(*this);

    updateActive();
  }
}

void ECS::render(float delay) {
  if (isStartScreen_) {
    SDL_RenderCopy(renderer_, title_.texture, nullptr, &title_.rect);
    SDL_RenderCopy(renderer_, start_.texture, nullptr, &start_.rect);
  } else {
    RenderSprite::render(*this, delay);
#ifdef DEBUG
    RenderCollider::render(*this);
#endif
  }
}

void ECS::initializeStartScreen() {
  TTF_Font* font =
      TTF_OpenFont("../../data/fonts/PressStart2P-Regular.ttf", 72);
  SDL_Color color = {255, 255, 255, 255};

  const char* title = "Space Cowboys";
  const char* start = "Press SPACE to start";

  SDL_Surface* titleSurface = TTF_RenderText_Solid(font, title, color);
  SDL_Surface* startSurface = TTF_RenderText_Solid(font, start, color);

  title_.texture = SDL_CreateTextureFromSurface(renderer_, titleSurface);
  start_.texture = SDL_CreateTextureFromSurface(renderer_, startSurface);

  int x = viewport_.w / 2 - titleSurface->w / 2;
  int y = viewport_.h / 2 - titleSurface->h / 2;
  title_.rect = {x, y, titleSurface->w, titleSurface->h};
  x = viewport_.w / 2 - startSurface->w / 2;
  y = viewport_.h / 2 - startSurface->h / 2 + titleSurface->h * 2;
  start_.rect = {x, y, startSurface->w, startSurface->h};

  SDL_FreeSurface(titleSurface);
  SDL_FreeSurface(startSurface);
}
