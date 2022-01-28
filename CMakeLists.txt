cmake_minimum_required(VERSION 3.15)

project(hello_world VERSION 0.1.0)

add_executable(hello_world "src/main.cpp")

# Compile with Clang and very strict warning level
target_compile_options(hello_world PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Set up tests
find_package(Catch2 3 REQUIRED)
add_executable(tests "src/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)