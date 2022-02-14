#define CATCH_CONFIG_MAIN

#include "vec2.h"

#include "catch.hpp"
#include "utils/utils.h"

Vec2 v = Vec2(1.0f, 2.0f);
Vec2 w = Vec2(3.0f, 4.0f);

TEST_CASE("Vec2 add", "[vec2]") {
  Vec2 u = v + w;
  REQUIRE(u == Vec2(4.0f, 6.0f));
  REQUIRE(u != Vec2(4.1f, 6.0f));
  REQUIRE(u != Vec2(4.0f, 6.1f));
}

TEST_CASE("Vec2 subtract", "[vec2]") {
  Vec2 u = v - w;
  REQUIRE(u == Vec2(-2.0f, -2.0f));
  REQUIRE(u != Vec2(-2.1f, -2.0f));
  REQUIRE(u != Vec2(-2.0f, -2.1f));
}

TEST_CASE("Vec2 multiply", "[vec2]") {
  Vec2 u = v * 1.5f;
  REQUIRE(u == Vec2(1.5f, 3.0f));
  REQUIRE(u != Vec2(1.6f, 3.0f));
  REQUIRE(u != Vec2(1.5f, 3.1f));
}

TEST_CASE("Vec2 divide", "[vec2]") {
  Vec2 u = v / 2.0f;
  REQUIRE(u == Vec2(0.5f, 1.0f));
  REQUIRE(u != Vec2(0.6f, 1.0f));
  REQUIRE(u != Vec2(0.5f, 1.1f));
}

TEST_CASE("Vec2 length", "[vec2]") {
  float length = v.length();
  REQUIRE(Utils::isEqual(length, sqrt(5)));
  REQUIRE(!Utils::isEqual(length, sqrt(4)));
  REQUIRE(!Utils::isEqual(length, sqrt(6)));
}

TEST_CASE("Vec2 normalize", "[vec2]") {
  float length = v.length();
  Vec2 u = v.normalize();
  REQUIRE(u == Vec2(v.x / length, v.y / length));
}

TEST_CASE("Vec2 limit", "[vec2]") {
  float length = v.length();
  float n = 0.5f;
  Vec2 u = v.limit(n);
  REQUIRE(u == Vec2(v.x / length * n, v.y / length * n));
}
