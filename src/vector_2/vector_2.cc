#include "vector_2.h"

#include <cmath>

Vector2::Vector2() : x(0.0), y(0.0) {}

Vector2::Vector2(double newX, double newY) : x(newX), y(newY) {}

Vector2 Vector2::add(Vector2 u, Vector2 v) {
  return Vector2(u.x + v.x, u.y + v.y);
}

Vector2 Vector2::subtract(Vector2 u, Vector2 v) {
  return Vector2(u.x - v.x, u.y - v.y);
}

Vector2 Vector2::multiply(Vector2 v, double n) {
  return Vector2(v.x * n, v.y * n);
}

Vector2 Vector2::divide(Vector2 v, double n) {
  return Vector2(v.x / n, v.y / n);
}

double Vector2::magnitude(Vector2 v) { return sqrt(v.x * v.x + v.y * v.y); }

Vector2 Vector2::normalize(Vector2 v) {
  double magnitude = Vector2::magnitude(v);
  if (magnitude > 0) {
    return Vector2::divide(v, magnitude);
  }
  return v;
}

Vector2 Vector2::limit(Vector2 v, double n) {
  if (Vector2::magnitude(v) > n) {
    Vector2 normal = Vector2::normalize(v);
    return Vector2::multiply(normal, n);
  }
  return v;
}

bool Vector2::operator==(const Vector2& other) {
  double error = 0.01;
  return abs(x - other.x) < error && abs(y - other.y) < error;
}
