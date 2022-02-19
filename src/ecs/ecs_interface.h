#pragma once

#include <SDL.h>

class ECSInterface {
 public:
  ECSInterface() : viewport_({0, 0, 0, 0}), renderer_(nullptr) {}
  virtual ~ECSInterface() = default;
  ECSInterface(const ECSInterface& other) = default;

  virtual void initialize() = 0;
  virtual void terminate() = 0;

  void setViewport(SDL_Rect viewport) { viewport_ = viewport; }
  const SDL_Rect viewport() { return viewport_; }

  void setRenderer(SDL_Renderer* renderer) { renderer_ = renderer; }
  const SDL_Renderer* renderer() { return renderer_; }

  virtual void input() = 0;
  virtual void update() = 0;
  virtual void render(float delay) = 0;

 protected:
  SDL_Rect viewport_;
  SDL_Renderer* renderer_;
};
