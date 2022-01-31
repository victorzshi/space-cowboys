cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(main LANGUAGES CXX VERSION 0.1.0)

# Build code with strict warning level
find_package(SDL2 CONFIG REQUIRED)
add_executable(main "src/main.cpp" "src/game/game.cpp")
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Unit testing
find_package(Catch2 CONFIG REQUIRED)
add_executable(tests "src/game/game.test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(tests)

# Smoke test
enable_testing()
add_test(NAME Runs COMMAND main)
