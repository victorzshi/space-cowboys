#define CATCH_CONFIG_MAIN

#include "vector_2.h"

#include "catch.hpp"

Vector2 u = Vector2(1.0, 2.0);
Vector2 v = Vector2(3.0, 4.0);
Vector2 w;

TEST_CASE("Vector2 add", "[vector_2]") {
  w = Vector2::add(u, v);
  REQUIRE((w == Vector2(4.0, 6.0)) == true);
  REQUIRE((w == Vector2(4.1, 6.0)) == false);
  REQUIRE((w == Vector2(4.0, 6.1)) == false);
}

TEST_CASE("Vector2 subtract", "[vector_2]") {
  w = Vector2::subtract(u, v);
  REQUIRE((w == Vector2(-2.0, -2.0)) == true);
  REQUIRE((w == Vector2(-2.1, -2.0)) == false);
  REQUIRE((w == Vector2(-2.0, -2.1)) == false);
}

TEST_CASE("Vector2 multiply", "[vector_2]") {
  w = Vector2::multiply(u, 1.5);
  REQUIRE((w == Vector2(1.5, 3.0)) == true);
  REQUIRE((w == Vector2(1.6, 3.0)) == false);
  REQUIRE((w == Vector2(1.5, 3.1)) == false);
}

TEST_CASE("Vector2 divide", "[vector_2]") {
  w = Vector2::divide(u, 2.0);
  REQUIRE((w == Vector2(0.5, 1.0)) == true);
  REQUIRE((w == Vector2(0.6, 1.0)) == false);
  REQUIRE((w == Vector2(0.5, 1.1)) == false);
}

TEST_CASE("Vector2 magnitude", "[vector_2]") {
  REQUIRE((Vector2::magnitude(u) == sqrt(5)) == true);
  REQUIRE((Vector2::magnitude(u) == sqrt(4)) == false);
  REQUIRE((Vector2::magnitude(u) == sqrt(6)) == false);
}

TEST_CASE("Vector2 normalize", "[vector_2]") {
  double magnitude = Vector2::magnitude(u);
  w = Vector2::normalize(u);
  REQUIRE((w.x == u.x / magnitude && w.y == u.y / magnitude) == true);
}

TEST_CASE("Vector2 limit", "[vector_2]") {
  double n = 2.0;
  double magnitude = Vector2::magnitude(u);
  w = Vector2::limit(u, n);
  REQUIRE((w == Vector2(u.x / magnitude * n, u.y / magnitude * n)) == true);
}
