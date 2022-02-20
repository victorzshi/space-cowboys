#pragma once

class Engine;
class Pool;

class RenderSprite {
 public:
  static void render(Engine& e, float delay);

 private:
  static void renderActive(Engine& e, float delay, Pool& pool);
};
