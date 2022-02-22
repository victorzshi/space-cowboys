#include "game.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <sstream>

Game::Game() : isRunning_(true) {
  window_ = SDL_CreateWindow("Space Cowboys", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
  if (window_ == nullptr) {
    fprintf(stderr, "Window could not be created! SDL Error: %s\n",
            SDL_GetError());
  }

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    fprintf(stderr, "Renderer could not be created! SDL Error: %s\n",
            SDL_GetError());
  }

  keyboard_ = SDL_GetKeyboardState(nullptr);
  if (keyboard_ == nullptr) {
    fprintf(stderr, "Keyboard could not be found! SDL Error: %s\n",
            SDL_GetError());
  }

  viewport_ = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

bool Game::initialize() {
  printf("Initializing game...\n");

  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL could not initialize! SDL Error: %s\n",
            SDL_GetError());
    success = false;
  }

  // Set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear")) {
    fprintf(stderr, "Warning: Linear texture filtering not enabled!\n");
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

  // Initialize entities
  ecs_.initialize(renderer_, keyboard_, viewport_);

  return success;
}

void Game::terminate() {
  ecs_.terminate();
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  TTF_Quit();
  SDL_Quit();
}

void Game::run(bool isSmokeTest) {
  // FPS COUNTER START
  Uint64 startTime = SDL_GetTicks64();
  Uint64 totalFrames = 0;
  TTF_Font* font =
      TTF_OpenFont("../../data/fonts/PressStart2P-Regular.ttf", 12);
  if (font == nullptr) {
    fprintf(stderr, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
  }
  SDL_Color color = {0, 255, 0, 255};
  std::stringstream text;
  SDL_Surface* surface = nullptr;
  SDL_Texture* texture = nullptr;
  SDL_Rect rect = {0, 0, 0, 0};
  // FPS COUNTER END

  Uint64 previous = SDL_GetTicks64();
  Uint64 lag = 0;

  SDL_Event event;

  while (isRunning_) {
    Uint64 current = SDL_GetTicks64();
    Uint64 elapsed = current - previous;
    previous = current;
    lag += elapsed;

    // Process input
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          isRunning_ = false;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              isRunning_ = false;
              break;
          }
          break;
      }
    }
    ecs_.input();

    // Update state
    while (lag >= TICKS_PER_UPDATE) {
      ecs_.update();
      lag -= TICKS_PER_UPDATE;

       // FPS COUNTER START
      Uint64 currentTime = SDL_GetTicks64();
      float totalSeconds = static_cast<float>(currentTime - startTime) / 1000;

      float fps = static_cast<float>(totalFrames) / totalSeconds;

      text.str("");
      text << fps;

      SDL_DestroyTexture(texture);
      surface = TTF_RenderText_Solid(font, text.str().c_str(), color);
      texture = SDL_CreateTextureFromSurface(renderer_, surface);
      rect = {0, 0, surface->w, surface->h};
      SDL_FreeSurface(surface);
      // FPS COUNTER END
    }

    // Render graphics
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);

    float delay = static_cast<float>(lag) / TICKS_PER_UPDATE;
    ecs_.render(delay);

    // FPS COUNTER START
    SDL_RenderCopy(renderer_, texture, nullptr, &rect);
    ++totalFrames;
    // FPS COUNTER END

    SDL_RenderPresent(renderer_);

    // Handle testing
    if (isSmokeTest && current > SMOKE_TEST_DURATION) {
      isRunning_ = false;
    }
  }
}
