#pragma once

class GameObject;
class Game;

class PhysicsComponent {
 public:
  virtual ~PhysicsComponent() {}
  virtual void update(GameObject& object, Game& game) = 0;
};
