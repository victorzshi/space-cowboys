#pragma once

#include <SDL.h>

#include "components/input_component.h"
#include "components/render_component.h"
#include "components/update_component.h"
#include "vector_2/vector_2.h"

class Game;

class GameObject {
 public:
  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;
  int width;
  int height;

  GameObject(InputComponent* input, UpdateComponent* update,
             RenderComponent* render);

  void input(SDL_Event event);

  void update(Game& game);

  void render(SDL_Renderer* renderer, double delay);

 private:
  InputComponent* input_;
  UpdateComponent* update_;
  RenderComponent* render_;
};
