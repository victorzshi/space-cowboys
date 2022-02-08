#pragma once

class Vector2 {
 public:
  double x, y;

  Vector2();

  Vector2(double x, double y);

  static Vector2 add(Vector2 u, Vector2 v);

  static Vector2 subtract(Vector2 u, Vector2 v);

  static Vector2 multiply(Vector2 v, double n);

  static Vector2 divide(Vector2 v, double n);

  static double magnitude(Vector2 v);

  static Vector2 normalize(Vector2 v);

  static Vector2 limit(Vector2 v, double n);

  bool operator==(const Vector2& other);
};
