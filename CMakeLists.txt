cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(main VERSION 0.1.0)

# Compile with Clang and very strict warning level
add_executable(main "src/main.cpp")
target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Set up unit testing
find_package(Catch2 CONFIG REQUIRED)
add_executable(tests "src/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(tests)

# Smoke test
enable_testing()
add_test(NAME Runs COMMAND main)
