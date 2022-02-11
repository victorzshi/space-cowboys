#define CATCH_CONFIG_MAIN

#include "vector_2.h"

#include "catch.hpp"

Vector2 u = Vector2(1.0, 2.0);
Vector2 v = Vector2(3.0, 4.0);
Vector2 w;

TEST_CASE("Vector2 add", "[vector_2]") {
  w = Vector2::add(u, v);
  REQUIRE((w.x == 4.0 && w.y == 6.0) == true);
  REQUIRE((w.x == 4.1 && w.y == 6.0) == false);
  REQUIRE((w.x == 4.0 && w.y == 6.1) == false);
}

TEST_CASE("Vector2 subtract", "[vector_2]") {
  w = Vector2::subtract(u, v);
  REQUIRE((w.x == -2.0 && w.y == -2.0) == true);
  REQUIRE((w.x == -2.1 && w.y == -2.0) == false);
  REQUIRE((w.x == -2.0 && w.y == -2.1) == false);
}

TEST_CASE("Vector2 multiply", "[vector_2]") {
  w = Vector2::multiply(u, 1.5);
  REQUIRE((w.x == 1.5 && w.y == 3.0) == true);
  REQUIRE((w.x == 1.6 && w.y == 3.0) == false);
  REQUIRE((w.x == 1.5 && w.y == 3.1) == false);
}

TEST_CASE("Vector2 divide", "[vector_2]") {
  w = Vector2::divide(u, 2.0);
  REQUIRE((w.x == 0.5 && w.y == 1.0) == true);
  REQUIRE((w.x == 0.6 && w.y == 1.0) == false);
  REQUIRE((w.x == 0.5 && w.y == 1.1) == false);
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
  REQUIRE((w.x == u.x / magnitude * n && w.y == u.y / magnitude * n) == true);
}
