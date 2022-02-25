#pragma once

enum class Direction { LEFT, RIGHT, DOWN };

class AI {
 public:
  Direction nextDirection;
  Direction prevDirection;
  float goalHeight;
  bool isPathEnd;
};
