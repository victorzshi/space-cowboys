#define CATCH_CONFIG_MAIN

#include "vec2.h"

#include "catch.hpp"
#include "utils/utils.h"

Vec2 u = Vec2(1.0, 2.0);
Vec2 v = Vec2(3.0, 4.0);
Vec2 w;

TEST_CASE("Vec2 add", "[vec2]") {
  w = Vec2::add(u, v);
  REQUIRE(Utils::isEqual(w.x, 4.0) == true);
  REQUIRE(Utils::isEqual(w.y, 6.0) == true);
  REQUIRE(Utils::isEqual(w.x, 4.1) == false);
  REQUIRE(Utils::isEqual(w.y, 6.1) == false);
}

TEST_CASE("Vec2 subtract", "[vec2]") {
  w = Vec2::subtract(u, v);
  REQUIRE(Utils::isEqual(w.x, -2.0) == true);
  REQUIRE(Utils::isEqual(w.y, -2.0) == true);
  REQUIRE(Utils::isEqual(w.x, -2.1) == false);
  REQUIRE(Utils::isEqual(w.y, -2.1) == false);
}

TEST_CASE("Vec2 multiply", "[vec2]") {
  w = Vec2::multiply(u, 1.5);
  REQUIRE(Utils::isEqual(w.x, 1.5) == true);
  REQUIRE(Utils::isEqual(w.y, 3.0) == true);
  REQUIRE(Utils::isEqual(w.x, 1.6) == false);
  REQUIRE(Utils::isEqual(w.y, 3.1) == false);
}

TEST_CASE("Vec2 divide", "[vec2]") {
  w = Vec2::divide(u, 2.0);
  REQUIRE(Utils::isEqual(w.x, 0.5) == true);
  REQUIRE(Utils::isEqual(w.y, 1.0) == true);
  REQUIRE(Utils::isEqual(w.x, 0.6) == false);
  REQUIRE(Utils::isEqual(w.y, 1.1) == false);
}

TEST_CASE("Vec2 magnitude", "[vec2]") {
  float magnitude = Vec2::magnitude(u);
  REQUIRE(Utils::isEqual(magnitude, sqrt(5)) == true);
}

TEST_CASE("Vec2 normalize", "[vec2]") {
  float magnitude = Vec2::magnitude(u);
  w = Vec2::normalize(u);
  REQUIRE(Utils::isEqual(w.x, u.x / magnitude) == true);
  REQUIRE(Utils::isEqual(w.y, u.y / magnitude) == true);
}

TEST_CASE("Vec2 limit", "[vec2]") {
  float n = 2.0f;
  float magnitude = Vec2::magnitude(u);
  w = Vec2::limit(u, n);
  REQUIRE(Utils::isEqual(w.x, u.x / magnitude * n) == true);
  REQUIRE(Utils::isEqual(w.y, u.y / magnitude * n) == true);
}
