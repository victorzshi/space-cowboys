#pragma once

#include "ecs_interface.h"

class ECS : public ECSInterface {
 public:
  ECS();

  virtual void initialize(SDL_Rect viewport, SDL_Renderer* renderer) override;
  virtual void terminate() override;

  virtual const SDL_Rect viewport() override;
  virtual const SDL_Renderer* renderer() override;

  virtual const Collider* collider() override;
  virtual const Physics* physics() override;
  virtual const Sprite* sprite() override;
  virtual const Transform* transform() override;

  virtual int createEntity() override;

  virtual void input() override;
  virtual void update() override;
  virtual void render(float delay) override;

 private:
  static const int MAX_ENTITIES = 100;

  SDL_Rect viewport_;
  SDL_Renderer* renderer_;

  Collider* collider_;
  Physics* physics_;
  Sprite* sprite_;
  Transform* transform_;

  int entity_;
};
