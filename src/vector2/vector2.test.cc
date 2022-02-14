#include "vector2.h"

#include "catch.hpp"
#include "utils/utils.h"

Vector2 v = {1.0f, 2.0f};
Vector2 w = {3.0f, 4.0f};

TEST_CASE("Vector2 add", "[vector2]") {
  Vector2 u = v + w;
  REQUIRE(u == Vector2{4.0f, 6.0f});
  REQUIRE(u != Vector2{4.1f, 6.0f});
  REQUIRE(u != Vector2{4.0f, 6.1f});
}

TEST_CASE("Vector2 subtract", "[vector2]") {
  Vector2 u = v - w;
  REQUIRE(u == Vector2{-2.0f, -2.0f});
  REQUIRE(u != Vector2{-2.1f, -2.0f});
  REQUIRE(u != Vector2{-2.0f, -2.1f});
}

TEST_CASE("Vector2 multiply", "[vector2]") {
  Vector2 u = v * 1.5f;
  REQUIRE(u == Vector2{1.5f, 3.0f});
  REQUIRE(u != Vector2{1.6f, 3.0f});
  REQUIRE(u != Vector2{1.5f, 3.1f});
}

TEST_CASE("Vector2 divide", "[vector2]") {
  Vector2 u = v / 2.0f;
  REQUIRE(u == Vector2{0.5f, 1.0f});
  REQUIRE(u != Vector2{0.6f, 1.0f});
  REQUIRE(u != Vector2{0.5f, 1.1f});
}

TEST_CASE("Vector2 length", "[vector2]") {
  float length = v.length();
  REQUIRE(Utils::isEqual(length, sqrt(5)));
  REQUIRE(!Utils::isEqual(length, sqrt(4)));
  REQUIRE(!Utils::isEqual(length, sqrt(6)));
}

TEST_CASE("Vector2 normalize", "[vector2]") {
  float length = v.length();
  Vector2 u = v.normalize();
  REQUIRE(u == Vector2{v.x / length, v.y / length});
}

TEST_CASE("Vector2 limit", "[vector2]") {
  float length = v.length();
  float n = 0.5f;
  Vector2 u = v.limit(n);
  REQUIRE(u == Vector2{v.x / length * n, v.y / length * n});
}
