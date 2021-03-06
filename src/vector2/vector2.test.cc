#define CATCH_CONFIG_MAIN

#include "vector2.h"

#include "catch.hpp"

Vector2 v = Vector2(1.0f, 2.0f);
Vector2 w = Vector2(3.0f, 4.0f);

TEST_CASE("Vector2 add", "[vector2]") {
  Vector2 u = v + w;
  REQUIRE(u == Vector2(4.0f, 6.0f));
#ifndef __unix__
  REQUIRE(u != Vector2(4.1f, 6.0f));
  REQUIRE(u != Vector2(4.0f, 6.1f));
#endif

  u += u;
  REQUIRE(u == Vector2(8.0f, 12.0f));
#ifndef __unix__
  REQUIRE(u != Vector2(8.1f, 12.0f));
  REQUIRE(u != Vector2(8.0f, 12.1f));
#endif
}

TEST_CASE("Vector2 subtract", "[vector2]") {
  Vector2 u = v - w;
  REQUIRE(u == Vector2(-2.0f, -2.0f));
#ifndef __unix__
  REQUIRE(u != Vector2(-2.1f, -2.0f));
  REQUIRE(u != Vector2(-2.0f, -2.1f));
#endif

  u -= u;
  REQUIRE(u == Vector2(0.0f, 0.0f));
#ifndef __unix__
  REQUIRE(u != Vector2(0.1f, 0.0f));
  REQUIRE(u != Vector2(0.0f, 0.1f));
#endif
}

TEST_CASE("Vector2 multiply", "[vector2]") {
  Vector2 u = v * 1.5f;
  REQUIRE(u == Vector2(1.5f, 3.0f));
#ifndef __unix__
  REQUIRE(u != Vector2(1.6f, 3.0f));
  REQUIRE(u != Vector2(1.5f, 3.1f));
#endif
}

TEST_CASE("Vector2 divide", "[vector2]") {
  Vector2 u = v / 2.0f;
  REQUIRE(u == Vector2(0.5f, 1.0f));
#ifndef __unix__
  REQUIRE(u != Vector2(0.6f, 1.0f));
  REQUIRE(u != Vector2(0.5f, 1.1f));
#endif
}

TEST_CASE("Vector2 length", "[vector2]") {
  float length = v.length();
  REQUIRE(Vector2::almostEquals(length, sqrt(5)));
#ifndef __unix__
  REQUIRE(!Vector2::almostEquals(length, sqrt(4)));
  REQUIRE(!Vector2::almostEquals(length, sqrt(6)));
#endif
}

TEST_CASE("Vector2 normalize", "[vector2]") {
  float length = v.length();
  Vector2 u = v.normalize();
  REQUIRE(u == Vector2(v.x / length, v.y / length));
}

TEST_CASE("Vector2 limit", "[vector2]") {
  float length = v.length();
  float n = 0.5f;
  Vector2 u = v.limit(n);
  REQUIRE(u == Vector2(v.x / length * n, v.y / length * n));
}
