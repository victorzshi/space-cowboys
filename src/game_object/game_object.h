#pragma once

#include <SDL.h>

#include "../vector_2/vector_2.h"
#include "components/graphics_component.h"
#include "components/input_component.h"
#include "components/physics_component.h"

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

  void render(SDL_Renderer* renderer);

 private:
  InputComponent* input_;
  PhysicsComponent* physics_;
  GraphicsComponent* graphics_;
};
