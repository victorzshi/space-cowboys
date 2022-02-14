#include "vec2.h"

#include <cmath>

Vec2::Vec2() : x(0.0f), y(0.0f) {}

Vec2::Vec2(float newX, float newY) : x(newX), y(newY) {}

Vec2 Vec2::add(Vec2 u, Vec2 v) { return Vec2(u.x + v.x, u.y + v.y); }

Vec2 Vec2::subtract(Vec2 u, Vec2 v) { return Vec2(u.x - v.x, u.y - v.y); }

Vec2 Vec2::multiply(Vec2 v, float n) { return Vec2(v.x * n, v.y * n); }

Vec2 Vec2::divide(Vec2 v, float n) { return Vec2(v.x / n, v.y / n); }

float Vec2::magnitude(Vec2 v) { return sqrt(v.x * v.x + v.y * v.y); }

Vec2 Vec2::normalize(Vec2 v) {
  float magnitude = Vec2::magnitude(v);
  if (magnitude > 0) {
    return Vec2::divide(v, magnitude);
  }
  return v;
}

Vec2 Vec2::limit(Vec2 v, float n) {
  if (Vec2::magnitude(v) > n) {
    Vec2 normal = Vec2::normalize(v);
    return Vec2::multiply(normal, n);
  }
  return v;
}
