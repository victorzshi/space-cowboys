#pragma once

#include <SDL.h>

class ECSInterface {
 public:
  ECSInterface() : viewport_({0, 0, 0, 0}), renderer_(nullptr) {
    // Initialize memory for component arrays
  }
  virtual ~ECSInterface() = default;
  ECSInterface(const ECSInterface& other) = default;

  void initialize(SDL_Rect viewport, SDL_Renderer* renderer) {
    viewport_ = viewport;
    renderer_ = renderer;
  }
  void terminate() {
    // Do stuff
  }

  const SDL_Rect viewport() { return viewport_; }
  const SDL_Renderer* renderer() { return renderer_; }

  // Array getters

  virtual void input() = 0;
  virtual void update() = 0;
  virtual void render(float delay) = 0;

 protected:
  SDL_Rect viewport_;
  SDL_Renderer* renderer_;

  // Arrays
};
