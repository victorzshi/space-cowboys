#define CATCH_CONFIG_MAIN

#include "vec_2.h"

#include "catch.hpp"

Vec2 u = Vec2(1.0, 2.0);
Vec2 v = Vec2(3.0, 4.0);
Vec2 w;

TEST_CASE("Vec2 add", "[vec_2]") {
  w = Vec2::add(u, v);
  REQUIRE((w.x == 4.0 && w.y == 6.0) == true);
  REQUIRE((w.x == 4.1 && w.y == 6.0) == false);
  REQUIRE((w.x == 4.0 && w.y == 6.1) == false);
}

TEST_CASE("Vec2 subtract", "[vec_2]") {
  w = Vec2::subtract(u, v);
  REQUIRE((w.x == -2.0 && w.y == -2.0) == true);
  REQUIRE((w.x == -2.1 && w.y == -2.0) == false);
  REQUIRE((w.x == -2.0 && w.y == -2.1) == false);
}

TEST_CASE("Vec2 multiply", "[vec_2]") {
  w = Vec2::multiply(u, 1.5);
  REQUIRE((w.x == 1.5 && w.y == 3.0) == true);
  REQUIRE((w.x == 1.6 && w.y == 3.0) == false);
  REQUIRE((w.x == 1.5 && w.y == 3.1) == false);
}

TEST_CASE("Vec2 divide", "[vec_2]") {
  w = Vec2::divide(u, 2.0);
  REQUIRE((w.x == 0.5 && w.y == 1.0) == true);
  REQUIRE((w.x == 0.6 && w.y == 1.0) == false);
  REQUIRE((w.x == 0.5 && w.y == 1.1) == false);
}

TEST_CASE("Vec2 magnitude", "[vec_2]") {
  REQUIRE((Vec2::magnitude(u) == sqrt(5)) == true);
  REQUIRE((Vec2::magnitude(u) == sqrt(4)) == false);
  REQUIRE((Vec2::magnitude(u) == sqrt(6)) == false);
}

TEST_CASE("Vec2 normalize", "[vec_2]") {
  double magnitude = Vec2::magnitude(u);
  w = Vec2::normalize(u);
  REQUIRE((w.x == u.x / magnitude && w.y == u.y / magnitude) == true);
}

TEST_CASE("Vec2 limit", "[vec_2]") {
  double n = 2.0;
  double magnitude = Vec2::magnitude(u);
  w = Vec2::limit(u, n);
  REQUIRE((w.x == u.x / magnitude * n && w.y == u.y / magnitude * n) == true);
}
