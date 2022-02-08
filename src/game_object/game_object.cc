#include "game_object.h"

GameObject::GameObject(InputComponent* input, UpdateComponent* update,
                       RenderComponent* render)
    : position(Vector2()),
      velocity(Vector2()),
      acceleration(Vector2()),
      width(0),
      height(0),
      input_(input),
      update_(update),
      render_(render) {}

void GameObject::input(SDL_Event event) { input_->update(*this, event); }

void GameObject::update(Game& game) { update_->update(*this, game); }

void GameObject::render(SDL_Renderer* renderer, double delay) {
  render_->update(*this, renderer, delay);
}

