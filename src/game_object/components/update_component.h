#pragma once

class GameObject;
class Game;

class UpdateComponent {
 public:
  virtual ~UpdateComponent() {}
  virtual void update(GameObject& object, Game& game) = 0;
};
