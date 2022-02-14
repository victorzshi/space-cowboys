#include "vector2.h"

#include "utils/utils.h"

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float newX, float newY) : x(newX), y(newY) {}

float Vector2::length() const { return sqrt(x * x + y * y); }

float Vector2::lengthSquared() const { return x * x + y * y; }

Vector2 Vector2::normalize() const {
  Vector2 v = *this / this->length();
  return v;
}

Vector2 Vector2::limit(float n) const {
  if (this->lengthSquared() > n * n) {
    Vector2 v = this->normalize() * n;
    return v;
  }
  return *this;
}

Vector2 Vector2::operator+(const Vector2& v) const {
  Vector2 u;
  u.x = this->x + v.x;
  u.y = this->y + v.y;
  return u;
}

Vector2 Vector2::operator-(const Vector2& v) const {
  Vector2 u;
  u.x = this->x - v.x;
  u.y = this->y - v.y;
  return u;
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
  return Utils::isEqual(x, v.x) && Utils::isEqual(y, v.y);
}

bool Vector2::operator!=(const Vector2& v) const {
  return !Utils::isEqual(x, v.x) || !Utils::isEqual(y, v.y);
}
