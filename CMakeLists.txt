cmake_minimum_required(VERSION 3.15)

project(space_invaders VERSION 0.1.0)

add_executable(space_invaders "src/main.cpp" "src/hello/hello.hpp")

# Compile with Clang and very strict warning level
target_compile_options(space_invaders PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Set up tests
find_package(Catch2 3 REQUIRED)
add_executable(tests "src/hello/hello.test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
