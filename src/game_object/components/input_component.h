#pragma once

class GameObject;
union SDL_Event;

class InputComponent {
 public:
  virtual ~InputComponent() {}
  virtual void update(GameObject& object, SDL_Event event) = 0;
};
