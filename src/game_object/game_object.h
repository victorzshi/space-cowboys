#pragma once

#include <SDL.h>

#include "components/graphics_component.h"
#include "components/input_component.h"
#include "components/physics_component.h"
#include "vector_2/vector_2.h"

class Game;

class GameObject {
 public:
  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;

  GameObject(InputComponent* input, PhysicsComponent* physics,
             GraphicsComponent* graphics);

  void processInput(SDL_Event event);

  void update(Game& game);

  void render(SDL_Renderer* renderer, double delay);

 private:
  InputComponent* input_;
  PhysicsComponent* physics_;
  GraphicsComponent* graphics_;
};
