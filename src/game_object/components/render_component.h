#pragma once

class GameObject;
struct SDL_Renderer;

class RenderComponent {
 public:
  virtual ~RenderComponent() {}
  virtual void update(GameObject& object, SDL_Renderer* renderer,
                      double delay) = 0;
};
