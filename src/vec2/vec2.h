#pragma once

class Vec2 {
 public:
  double x, y;

  Vec2();

  Vec2(double x, double y);

  static Vec2 add(Vec2 u, Vec2 v);

  static Vec2 subtract(Vec2 u, Vec2 v);

  static Vec2 multiply(Vec2 v, double n);

  static Vec2 divide(Vec2 v, double n);

  static double magnitude(Vec2 v);

  static Vec2 normalize(Vec2 v);

  static Vec2 limit(Vec2 v, double n);
};
