#pragma once

#include <string>

#include "types/types.h"

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;

class AI;
class Collider;
class Physics;
class Sprite;
class Timer;
class Transform;

class Aliens;
class Bullets;
class Explosions;
class Particles;
class Tanks;
class Zappers;

enum class Screen { START, WIN, LOSE, PAUSED, NONE };

class Active {
 public:
  int* ids;
  int size;
};

class Engine {
 public:
  Engine() {}
  virtual ~Engine() = default;
  Engine(const Engine& other) = default;

  // Manage memory
  virtual void initialize(SDL_Renderer* renderer, const Uint8* keyboard,
                          SDL_Rect& viewport) = 0;
  virtual void terminate() = 0;

  // Get globals
  virtual SDL_Renderer* renderer() = 0;
  virtual const Uint8* keyboard() = 0;
  virtual SDL_Rect& viewport() = 0;
  virtual Screen screen() = 0;

  // Get component arrays
  virtual AI* ai() = 0;
  virtual Collider* collider() = 0;
  virtual Physics* physics() = 0;
  virtual Sprite* sprite() = 0;
  virtual Timer* timer() = 0;
  virtual Transform* transform() = 0;

  // Get object pools
  virtual Active& active() = 0;
  virtual Aliens& aliens() = 0;
  virtual Explosions& explosions() = 0;
  virtual Bullets& bullets() = 0;
  virtual Particles& particles() = 0;
  virtual Tanks& tanks() = 0;
  virtual Zappers& zappers() = 0;

  // Setters
  virtual void setScreen(Screen screen) = 0;

  // Manage entities
  virtual int createEntity() = 0;
  virtual void updateActive() = 0;

  // Utilities
  virtual Sprite createSpriteFromFile(std::string file) = 0;
  virtual Sprite createSpriteFromText(std::string text, int fontSize) = 0;
  virtual bool isOutOfBounds(SDL_Rect rect) = 0;
  virtual bool isOutOfBoundsWidth(SDL_Rect rect) = 0;
  virtual bool isOutOfBoundsTop(SDL_Rect rect, int offset) = 0;
  virtual bool isOutOfBoundsBottom(SDL_Rect rect, int offset) = 0;
  virtual float random(float min, float max) = 0;

  // Game loop
  virtual void input() = 0;
  virtual void update() = 0;
  virtual void render(float delay) = 0;
};
