#pragma once

#include <string>

#include "types/types.h"

struct SDL_Rect;
struct SDL_Renderer;
struct SDL_Texture;

struct AI;
struct Collider;
struct Physics;
struct Sprite;
struct Timer;
struct Transform;

class Aliens;
class Bullets;
class Tanks;

struct Active {
  int* ids;
  int size;
};

class Engine {
 public:
  Engine() {}
  virtual ~Engine() = default;
  Engine(const Engine& other) = default;

  virtual void initialize(SDL_Renderer* renderer, SDL_Rect& viewport,
                          const Uint8* keyboard) = 0;
  virtual void terminate() = 0;

  virtual SDL_Renderer* renderer() = 0;
  virtual SDL_Rect& viewport() = 0;
  virtual const Uint8* keyboard() = 0;

  virtual AI* ai() = 0;
  virtual Collider* collider() = 0;
  virtual Physics* physics() = 0;
  virtual Sprite* sprite() = 0;
  virtual Timer* timer() = 0;
  virtual Transform* transform() = 0;

  virtual Active& active() = 0;
  virtual Aliens& aliens() = 0;
  virtual Bullets& bullets() = 0;
  virtual Tanks& tanks() = 0;

  virtual int createEntity() = 0;
  virtual SDL_Texture* createTexture(std::string file) = 0;
  virtual bool isOutOfBounds(SDL_Rect rect) = 0;
  virtual bool isOutOfBoundsWidth(SDL_Rect rect) = 0;
  virtual void updateActive() = 0;

  virtual void input() = 0;
  virtual void update() = 0;
  virtual void render(float delay) = 0;
};
