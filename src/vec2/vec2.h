#pragma once

class Vec2 {
 public:
  float x, y;

  Vec2();

  Vec2(float x, float y);

  float length() const;

  float lengthSquared() const;

  Vec2 normalize() const;

  Vec2 limit(float n) const;

  Vec2 operator+(const Vec2& v) const;

  Vec2 operator-(const Vec2& v) const;

  Vec2 operator*(float n) const;

  Vec2 operator/(float n) const;

  bool operator==(const Vec2& v) const;

  bool operator!=(const Vec2& v) const;
};
