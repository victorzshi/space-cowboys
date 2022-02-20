#pragma once

enum class Direction { LEFT, RIGHT, DOWN };

struct AI {
  Direction nextDirection;
  Direction prevDirection;
  float goalHeight;
  bool isPathEnd;
};
