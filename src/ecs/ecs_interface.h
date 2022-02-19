#pragma once

#include <SDL.h>
#include <vector2/vector2.h>

#include "components/collider.h"
#include "components/physics.h"
#include "components/sprite.h"
#include "components/transform.h"

class ECSInterface {
 public:
  ECSInterface() {}
  virtual ~ECSInterface() = default;
  ECSInterface(const ECSInterface& other) = default;

  virtual void initialize(SDL_Rect viewport, SDL_Renderer* renderer) = 0;
  virtual void terminate() = 0;

  virtual const SDL_Rect viewport() = 0;
  virtual const SDL_Renderer* renderer() = 0;

  virtual const Collider* collider() = 0;
  virtual const Physics* physics() = 0;
  virtual const Sprite* sprite() = 0;
  virtual const Transform* transform() = 0;

  virtual int createEntity() = 0;

  virtual void input() = 0;
  virtual void update() = 0;
  virtual void render(float delay) = 0;
};
