#define SDL_MAIN_HANDLED

#include "SDL.h"

int main() {
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
  const int STAY_ALIVE = 3000;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window =
      SDL_CreateWindow("SDL2Test", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  SDL_Delay(STAY_ALIVE);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
