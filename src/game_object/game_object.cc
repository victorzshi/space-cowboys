#include "game_object.h"

GameObject::GameObject(InputComponent* input, PhysicsComponent* physics,
                       GraphicsComponent* graphics)
    : position(Vector2()),
      velocity(Vector2()),
      input_(input),
      physics_(physics),
      graphics_(graphics) {}

void GameObject::processInput(SDL_Event event) { input_->update(*this, event); }

void GameObject::update(Game& game) { physics_->update(*this, game); }

void GameObject::render(SDL_Renderer* renderer) {
  graphics_->update(*this, renderer);
}
