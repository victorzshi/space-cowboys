#pragma once

class GameObject;
struct SDL_Renderer;

class GraphicsComponent {
 public:
  virtual ~GraphicsComponent() {}
  virtual void update(GameObject& object, SDL_Renderer* renderer) = 0;
};
