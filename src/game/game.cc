#include "game.h"

#include <SDL_image.h>

Game::Game() : isRunning_(true), isFullscreen_(false) {}

bool Game::initialize() {
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL could not initialize! SDL Error: %s\n",
            SDL_GetError());
    success = false;
  }

  // Enable texture filtering
  if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best") != SDL_TRUE) {
    fprintf(stderr, "Warning: Texture filtering not enabled!\n");
  }

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n",
            IMG_GetError());
    success = false;
  }

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n",
            TTF_GetError());
    success = false;
  }

  // Create global window
  window_ = SDL_CreateWindow("Space Cowboys", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window_ == nullptr) {
    fprintf(stderr, "Window could not be created! SDL Error: %s\n",
            SDL_GetError());
    success = false;
  }

  // Create global renderer
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == nullptr) {
    fprintf(stderr, "Renderer could not be created! SDL Error: %s\n",
            SDL_GetError());
    success = false;
  }

  // Set device independent resolution
  if (SDL_RenderSetLogicalSize(renderer_, SCREEN_WIDTH, SCREEN_HEIGHT) != 0) {
    fprintf(stderr, "Warning: Renderer logical size not set! SDL Error: %s\n",
            SDL_GetError());
  }

  // Set global keyboard
  keyboard_ = SDL_GetKeyboardState(nullptr);
  if (keyboard_ == nullptr) {
    fprintf(stderr, "Keyboard could not be found! SDL Error: %s\n",
            SDL_GetError());
    success = false;
  }

  // Set global viewport
  viewport_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

  // Initialize entities
  ecs_.initialize(renderer_, keyboard_, viewport_);

  // Initialize FPS counter
  fps_.font = TTF_OpenFont("../../data/fonts/PressStart2P-Regular.ttf", 12);
  if (fps_.font == nullptr) {
    fprintf(stderr, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  }
  fps_.color = {0, 255, 0, 255};
  fps_.texture = nullptr;
  fps_.rect = {0, 0, 0, 0};
  fps_.ticks = SDL_GetTicks64();
  fps_.frames = 0;
  fps_.text.str("");

  return success;
}

void Game::terminate() {
  ecs_.terminate();

  TTF_CloseFont(fps_.font);
  fps_.font = nullptr;
  SDL_DestroyTexture(fps_.texture);
  fps_.texture = nullptr;

  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  TTF_Quit();
  SDL_Quit();
}

void Game::run(bool isSmokeTest) {
  Uint64 previous = SDL_GetTicks64();
  Uint64 lag = 0;

  SDL_Event event;

  while (isRunning_) {
    Uint64 current = SDL_GetTicks64();
    Uint64 elapsed = current - previous;
    previous = current;
    lag += elapsed;

    while (lag >= TICKS_PER_UPDATE) {
      // Process input
      while (SDL_PollEvent(&event) != 0) {
        handleEvent(event);
      }
      ecs_.input();

      // Update state
      ecs_.update();
      lag -= TICKS_PER_UPDATE;

      Uint64 ticks = current - fps_.ticks;
      float seconds = static_cast<float>(ticks) / 1000;
      float fps = static_cast<float>(fps_.frames) / seconds;

      fps_.text.str("");
      fps_.text << fps;

      SDL_DestroyTexture(fps_.texture);
      SDL_Surface* surface =
          TTF_RenderText_Solid(fps_.font, fps_.text.str().c_str(), fps_.color);
      fps_.texture = SDL_CreateTextureFromSurface(renderer_, surface);
      fps_.rect = {0, 0, surface->w, surface->h};
      SDL_FreeSurface(surface);
    }

    // Render graphics
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);

    float delay = static_cast<float>(lag) / TICKS_PER_UPDATE;
    ecs_.render(delay);

    SDL_RenderCopy(renderer_, fps_.texture, nullptr, &fps_.rect);

    SDL_RenderPresent(renderer_);
    fps_.frames++;

    // Reset FPS counter every second
    if (current - fps_.ticks > 1000) {
      fps_.ticks = current;
      fps_.frames = 0;
    }

    // Handle testing
    if (isSmokeTest && current > SMOKE_TEST_DURATION) {
      isRunning_ = false;
    }
  }
}

void Game::handleEvent(SDL_Event event) {
  if (event.type == SDL_QUIT) {
    isRunning_ = false;
    return;
  }

  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        ecs_.setScreen(Screen::PAUSED);
        break;

      case SDLK_f:
        toggleFullscreen();
        ecs_.setScreen(Screen::PAUSED);
        break;
    }
  }
}

void Game::toggleFullscreen() {
  if (isFullscreen_) {
    int result = SDL_SetWindowFullscreen(window_, 0);

    if (result != 0) {
      fprintf(stderr,
              "Warning: Window not set to windowed mode! SDL Error: %s\n",
              SDL_GetError());
    } else {
      isFullscreen_ = false;
    }
  } else {
    int result =
        SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (result != 0) {
      fprintf(stderr, "Warning: Window not set to fullscreen! SDL Error: %s\n",
              SDL_GetError());
    } else {
      isFullscreen_ = true;
    }
  }
}
