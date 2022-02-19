#pragma once

#include "ecs_interface.h"
#include "pools/bullets.h"

class ECS : public ECSInterface {
 public:
  ECS();

  virtual void initialize(SDL_Rect viewport, SDL_Renderer* renderer) override;
  virtual void terminate() override;

  virtual SDL_Rect& viewport() override;
  virtual SDL_Renderer* renderer() override;

  virtual Collider* collider() override;
  virtual Physics* physics() override;
  virtual Sprite* sprite() override;
  virtual Transform* transform() override;

  virtual Bullets& bullets() override;

  virtual int createEntity() override;

  virtual void input() override;
  virtual void update() override;
  virtual void render(float delay) override;

 private:
  static const int MAX_ENTITIES = 1000;

  int id_;

  SDL_Rect viewport_;
  SDL_Renderer* renderer_;

  Collider* collider_;
  Physics* physics_;
  Sprite* sprite_;
  Transform* transform_;

  Bullets bullets_;
};
