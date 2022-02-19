#include "vector2.h"

#include <assert.h>

#include <cmath>

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float newX, float newY) : x(newX), y(newY) {}

float Vector2::length() const { return sqrt(x * x + y * y); }

float Vector2::lengthSquared() const { return x * x + y * y; }

Vector2 Vector2::normalize() const {
  assert(this->length() > 0);
  Vector2 v = *this / this->length();
  return v;
}

Vector2 Vector2::limit(float n) const {
  Vector2 v = *this;
  if (this->lengthSquared() > n * n) {
    v = this->normalize() * n;
  }
  return v;
}

Vector2 Vector2::operator+(const Vector2& v) const {
  Vector2 u;
  u.x = this->x + v.x;
  u.y = this->y + v.y;
  return u;
}

Vector2& Vector2::operator+=(const Vector2& v) {
  x += v.x;
  y += v.y;
  return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const {
  Vector2 u;
  u.x = this->x - v.x;
  u.y = this->y - v.y;
  return u;
}

Vector2& Vector2::operator-=(const Vector2& v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

Vector2 Vector2::operator*(float n) const {
  Vector2 u;
  u.x = this->x * n;
  u.y = this->y * n;
  return u;
}

Vector2 Vector2::operator/(float n) const {
  Vector2 u;
  u.x = this->x / n;
  u.y = this->y / n;
  return u;
}

bool Vector2::operator==(const Vector2& v) const {
  return isEqual(x, v.x) && isEqual(y, v.y);
}

bool Vector2::operator!=(const Vector2& v) const {
  return !isEqual(x, v.x) || !isEqual(y, v.y);
}

bool Vector2::isEqual(float a, float b) {
  float epsilon = 1.0f / 1000;
  return abs(a - b) <= epsilon * (abs(a) + abs(b) + 1.0f);
}
