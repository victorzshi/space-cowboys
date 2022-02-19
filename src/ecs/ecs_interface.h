#pragma once

struct SDL_Rect;
struct SDL_Renderer;

struct Collider;
struct Physics;
struct Sprite;
struct Transform;

class Bullets;

class ECSInterface {
 public:
  ECSInterface() {}
  virtual ~ECSInterface() = default;
  ECSInterface(const ECSInterface& other) = default;

  virtual void initialize(SDL_Rect viewport, SDL_Renderer* renderer) = 0;
  virtual void terminate() = 0;

  virtual SDL_Rect& viewport() = 0;
  virtual SDL_Renderer* renderer() = 0;

  virtual Collider* collider() = 0;
  virtual Physics* physics() = 0;
  virtual Sprite* sprite() = 0;
  virtual Transform* transform() = 0;

  virtual Bullets& bullets() = 0;

  virtual int createEntity() = 0;

  virtual void input() = 0;
  virtual void update() = 0;
  virtual void render(float delay) = 0;
};
