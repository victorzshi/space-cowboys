#pragma once

struct Vector2 {
  float x, y;

  Vector2();

  Vector2(float x, float y);

  float length() const;

  float lengthSquared() const;

  Vector2 normalize() const;

  Vector2 limit(float n) const;

  Vector2 operator+(const Vector2& v) const;

  Vector2& operator+=(const Vector2& v);

  Vector2 operator-(const Vector2& v) const;

  Vector2& operator-=(const Vector2& v);

  Vector2 operator*(float n) const;

  Vector2 operator/(float n) const;

  bool operator==(const Vector2& v) const;

  bool operator!=(const Vector2& v) const;

  static bool isEqual(float a, float b, float epsilon = 1.0f / 1000);
};
