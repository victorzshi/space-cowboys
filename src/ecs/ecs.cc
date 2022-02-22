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
      screen_(Screen::START),
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

  initializePools();
  initializeText();
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
Screen ECS::screen() { return screen_; }

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

void ECS::setScreen(Screen screen) { screen_ = screen; }

int ECS::createEntity() {
  assert(id_ < MAX_ENTITIES);
  id_++;
  return id_ - 1;  // Array index starts at 0
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

Sprite ECS::createSpriteFromFile(std::string file) {
#ifdef DEBUG
  std::string path = "../../data/images/" + file;
#else
  std::string path = "data/images/" + file;
#endif
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n", file.c_str(),
           IMG_GetError());
  }

  Sprite sprite;
  sprite.texture = SDL_CreateTextureFromSurface(renderer_, surface);
  if (sprite.texture == nullptr) {
    printf("Unable to create texture from %s! SDL Error: %s\n", file.c_str(),
           SDL_GetError());
  }

  sprite.target.x = viewport_.w / 2 - surface->w / 2;
  sprite.target.y = viewport_.h / 2 - surface->h / 2;
  sprite.target.w = surface->w;
  sprite.target.h = surface->h;

  SDL_FreeSurface(surface);

  return sprite;
}

Sprite ECS::createSpriteFromText(std::string text, int fontSize) {
#ifdef DEBUG
  TTF_Font* font =
      TTF_OpenFont("../../data/fonts/PressStart2P-Regular.ttf", fontSize);
#else
  TTF_Font* font =
      TTF_OpenFont("data/fonts/PressStart2P-Regular.ttf", fontSize);
#endif
  if (font == nullptr) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
  }

  SDL_Color color = {255, 255, 255, 255};

  SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (surface == nullptr) {
    printf("Unable to load image %s! SDL_image Error: %s\n", text.c_str(),
           IMG_GetError());
  }

  Sprite sprite;
  sprite.texture = SDL_CreateTextureFromSurface(renderer_, surface);
  if (sprite.texture == nullptr) {
    printf("Unable to create texture from %s! SDL Error: %s\n", text.c_str(),
           SDL_GetError());
  }

  sprite.target.x = viewport_.w / 2 - surface->w / 2;
  sprite.target.y = viewport_.h / 2 - surface->h / 2;
  sprite.target.w = surface->w;
  sprite.target.h = surface->h;

  SDL_FreeSurface(surface);

  return sprite;
}

bool ECS::isOutOfBounds(SDL_Rect rect) {
  return rect.x < viewport_.x || rect.x + rect.w > viewport_.w ||
         rect.y < viewport_.y || rect.y + rect.h > viewport_.h;
}

bool ECS::isOutOfBoundsWidth(SDL_Rect rect) {
  return rect.x < viewport_.x || rect.x + rect.w > viewport_.w;
}

bool ECS::isOutOfBoundsTop(SDL_Rect rect, int offset) {
  return rect.y < viewport_.y + offset;
}

bool ECS::isOutOfBoundsBottom(SDL_Rect rect, int offset) {
  return rect.y + rect.h > viewport_.h + offset;
}

float ECS::random(float min, float max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(min, max);
  return dis(gen);
}

void ECS::input() {
  switch (screen_) {
    case Screen::START:
      if (keyboard_[SDL_SCANCODE_SPACE]) {
        SDL_DestroyTexture(subtitle_.texture);
        subtitle_.texture = nullptr;
        screen_ = Screen::NONE;
      }
      return;
    case Screen::WIN:
      if (subtitle_.texture == nullptr) {
        int score = tanks_.size() - tanks_.begin();
        std::string text = "You win!!! ";
        if (score == 1) {
          text += std::to_string(score) + " cowboy left.";
        } else {
          text += std::to_string(score) + " cowboys left.";
        }

        subtitle_ = createSpriteFromText(text, 36);
        subtitle_.target.y += title_.target.h * 2;

        text_ = createSpriteFromText("Press F to restart", 36);
        text_.target.y += title_.target.h * 3;
      }
      if (keyboard_[SDL_SCANCODE_F]) {
        initializePools();
        SDL_DestroyTexture(subtitle_.texture);
        subtitle_.texture = nullptr;
        screen_ = Screen::NONE;
      }
      break;
    case Screen::LOSE:
      if (subtitle_.texture == nullptr) {
        int score = aliens_.size() - aliens_.begin();
        std::string text = "You lose... ";
        if (score == 1) {
          text += std::to_string(score) + " alien left.";
        } else {
          text += std::to_string(score) + " aliens left.";
        }

        subtitle_ = createSpriteFromText(text, 36);
        subtitle_.target.y += title_.target.h * 2;

        text_ = createSpriteFromText("Press F to restart", 36);
        text_.target.y += title_.target.h * 3;
      }
      if (keyboard_[SDL_SCANCODE_F]) {
        initializePools();
        SDL_DestroyTexture(subtitle_.texture);
        subtitle_.texture = nullptr;
        screen_ = Screen::NONE;
      }
      break;
    case Screen::NONE:
      if (keyboard_[SDL_SCANCODE_F]) {
        initializePools();
      }
      break;
  }
  InputPlayer::input(*this);
  InputAI::input(*this);
  updateActive();
}

void ECS::update() {
  UpdatePosition::update(*this);
  UpdateTanks::update(*this);
  UpdateAliens::update(*this);
  UpdateHit::update(*this);
  UpdateEffects::update(*this);
  updateActive();
}

void ECS::render(float delay) {
  if (screen_ != Screen::NONE) {
    SDL_RenderCopy(renderer_, title_.texture, nullptr, &title_.target);
    SDL_RenderCopy(renderer_, subtitle_.texture, nullptr, &subtitle_.target);
    SDL_RenderCopy(renderer_, text_.texture, nullptr, &text_.target);
  }
  RenderSprite::render(*this, delay);
#ifdef DEBUG
  RenderCollider::render(*this);
#endif
}

void ECS::initializePools() {
  id_ = 0;
  aliens_.initialize();
  bullets_.initialize();
  explosions_.initialize();
  particles_.initialize();
  tanks_.initialize();
  zappers_.initialize();
}

void ECS::initializeText() {
  title_ = createSpriteFromText("Space Cowboys", 72);
  subtitle_ = createSpriteFromText("Press SPACE", 36);
  text_ = createSpriteFromText("Move with arrow keys", 36);

  subtitle_.target.y += title_.target.h * 2;
  text_.target.y += title_.target.h * 3;
}
