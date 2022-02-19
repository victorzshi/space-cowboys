#pragma once

enum class Direction { kLeft, kRight, kDown };

struct AI {
  Direction nextDirection;
  Direction prevDirection;
  float goalHeight;
  bool isPathEnd;
};
