#pragma once

#include <sstream>

#include "ecs/ecs.h"
#include "types/types.h"

class FPS {
 public:
  TTF_Font* font;
  SDL_Color color;
  SDL_Texture* texture;
  SDL_Rect rect;
  Uint64 ticks;
  Uint64 frames;
  std::stringstream text;
};

class Game {
 public:
  Game();

  bool initialize();
  void terminate();

  void run(bool isSmokeTest = false);

 private:
  static const int SCREEN_WIDTH = 1366;
  static const int SCREEN_HEIGHT = 768;
  static const int TICKS_PER_UPDATE = 16;
  static const int SMOKE_TEST_DURATION = 1000;

  bool isRunning_;
  bool isVSync_;
  bool isFullscreen_;

  SDL_Window* window_;
  SDL_Renderer* renderer_;
  const Uint8* keyboard_;
  SDL_Rect viewport_;

  ECS ecs_;

  FPS fps_;

  // Non-gameplay events
  void handleEvent(SDL_Event event);
  void disableVSync();
  void toggleFullscreen();
};
