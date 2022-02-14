#pragma once

class Vec2 {
 public:
  float x, y;

  Vec2();

  Vec2(float x, float y);

  static Vec2 add(Vec2 u, Vec2 v);

  static Vec2 subtract(Vec2 u, Vec2 v);

  static Vec2 multiply(Vec2 v, float n);

  static Vec2 divide(Vec2 v, float n);

  static float magnitude(Vec2 v);

  static Vec2 normalize(Vec2 v);

  static Vec2 limit(Vec2 v, float n);
};
