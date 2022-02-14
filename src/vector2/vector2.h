#pragma once

struct Vector2 {
  float x = 0.0f;
  float y = 0.0f;

  float length() const;

  float lengthSquared() const;

  Vector2 normalize() const;

  Vector2 limit(float n) const;

  Vector2 operator+(const Vector2& v) const;

  Vector2 operator-(const Vector2& v) const;

  Vector2 operator*(float n) const;

  Vector2 operator/(float n) const;

  bool operator==(const Vector2& v) const;

  bool operator!=(const Vector2& v) const;
};
