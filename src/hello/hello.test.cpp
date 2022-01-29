#include <catch2/catch_test_macros.hpp>

#include "hello.hpp"

TEST_CASE("Show Hello World") {
  REQUIRE(Hello::get_greeting() == "Hello World\n");
}
