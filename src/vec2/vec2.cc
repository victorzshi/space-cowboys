#include "vec2.h"

#include "utils/utils.h"

Vec2::Vec2() : x(0.0f), y(0.0f) {}

Vec2::Vec2(float newX, float newY) : x(newX), y(newY) {}

float Vec2::length() const { return sqrt(x * x + y * y); }

float Vec2::lengthSquared() const { return x * x + y * y; }

Vec2 Vec2::normalize() const {
  Vec2 v = *this / this->length();
  return v;
}

Vec2 Vec2::limit(float n) const {
  if (this->lengthSquared() > n * n) {
    Vec2 v = this->normalize() * n;
    return v;
  }
  return *this;
}

Vec2 Vec2::operator+(const Vec2& v) const {
  Vec2 u;
  u.x = this->x + v.x;
  u.y = this->y + v.y;
  return u;
}

Vec2 Vec2::operator-(const Vec2& v) const {
  Vec2 u;
  u.x = this->x - v.x;
  u.y = this->y - v.y;
  return u;
}

Vec2 Vec2::operator*(float n) const {
  Vec2 u;
  u.x = this->x * n;
  u.y = this->y * n;
  return u;
}

Vec2 Vec2::operator/(float n) const {
  Vec2 u;
  u.x = this->x / n;
  u.y = this->y / n;
  return u;
}

bool Vec2::operator==(const Vec2& v) const {
  return Utils::isEqual(x, v.x) && Utils::isEqual(y, v.y);
}

bool Vec2::operator!=(const Vec2& v) const {
  return !Utils::isEqual(x, v.x) || !Utils::isEqual(y, v.y);
}
