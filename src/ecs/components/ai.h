#pragma once

enum class Direction { kNone, kLeft, kRight, kDown };

struct AI {
  Direction nextDirection = Direction::kNone;
  Direction prevDirection = Direction::kNone;
  float goalHeight = 0.0f;
  bool isPathEnd = false;
};
