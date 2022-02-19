#pragma once

struct SDL_Rect;
struct SDL_Point;
struct SDL_Renderer;
struct SDL_Texture;

struct Vector2;

class Utils {
 public:
  // Position is the center of the rect.
  static SDL_Point topLeftPoint(Vector2 position, SDL_Rect rect);

  static bool isEqual(float a, float b, float epsilon = 1.0f / 1000);

  static SDL_Texture* createTexture(SDL_Renderer* renderer, const char* file);

  static bool isOutOfBounds(SDL_Rect box);
};
