#include "entities.h"

#include <SDL_image.h>
#include <assert.h>
#include <time.h>

#include "systems/movement.h"
#include "systems/render_sprite.h"
#include "systems/update_position.h"

Entities::Entities() : size_(0) {}

void Entities::initialize(int screenWidth, int screenHeight,
                          SDL_Renderer* renderer) {
  physics_ = new Physics[kMaxSize];
  sprites_ = new Sprite[kMaxSize];
  transforms_ = new Transform[kMaxSize];

  // Load space invader image
  SDL_Texture* spaceInvader = nullptr;
  SDL_Surface* loadedSurface = IMG_Load("../../data/space-invader.png");
  spaceInvader = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
  Sprite sprite = {spaceInvader};

  // Initialize random number
  unsigned int seed = static_cast<unsigned int>(time(nullptr));
  srand(seed);

  for (int i = 0; i < kMaxSize; i++) {
    int entity = createEntity();
    int width = rand() % screenWidth;
    int height = rand() % screenHeight;
    addTransform(entity, {Vec2(width, height), 50, 50});
    addPhysics(entity, {0.1, Vec2(0.0, rand() % 5 + 1)});
    addSprite(entity, sprite);
  }

#ifdef DEBUG
  start_time = static_cast<int>(SDL_GetTicks64());
  frame_total = 0;
  update_total = 0;
  debug_font = TTF_OpenFont("../../data/fonts/PressStart2P-Regular.ttf", 32);
  debug_font_color = {255, 255, 255, 255};
#endif
}

int Entities::size() { return size_; }

Physics* Entities::physics() { return physics_; }

Sprite* Entities::sprites() { return sprites_; }

Transform* Entities::transforms() { return transforms_; }

void Entities::input(SDL_Event event) {
  //
  Movement::input(*this, event);
}

void Entities::update(SDL_Renderer* renderer) {
  UpdatePosition::update(*this);
#ifdef DEBUG
  int current_time = static_cast<int>(SDL_GetTicks64());
  double total_time = (current_time - start_time) / 1000.0;

  double average_frames_per_second = frame_total / total_time;
  frame_text.str("");
  frame_text << "Average Frames Per Second " << average_frames_per_second;

  double average_updates_per_second = update_total / total_time;
  update_text.str("");
  update_text << "Average Updates Per Second " << average_updates_per_second;

  frames_per_second_texture.load_text(
      renderer, debug_font, frame_text.str().c_str(), debug_font_color);
  updates_per_second_texture.load_text(
      renderer, debug_font, update_text.str().c_str(), debug_font_color);

  ++update_total;
#endif
}

void Entities::render(SDL_Renderer* renderer, double delay) {
  RenderSprite::render(*this, renderer, delay);
#ifdef DEBUG
  frames_per_second_texture.render(renderer, 0, 0);
  updates_per_second_texture.render(renderer, 0,
                                    frames_per_second_texture.get_height());

  ++frame_total;
#endif
}

int Entities::createEntity() {
  assert(size_ < kMaxSize);

  ++size_;
  return size_ - 1;
}

void Entities::addPhysics(int entity, Physics physics) {
  physics_[entity] = physics;
}

void Entities::addSprite(int entity, Sprite sprite) {
  sprites_[entity] = sprite;
}

void Entities::addTransform(int entity, Transform transform) {
  transforms_[entity] = transform;
}
