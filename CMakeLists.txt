cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(main LANGUAGES CXX VERSION 0.1.0)

# Find dependencies
find_package(SDL2 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Compile with very strict warning level
add_executable(main)
target_sources(main PRIVATE "src/main.cpp")
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_compile_options(main PRIVATE
  $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic -Werror>
  $<$<CXX_COMPILER_ID:MSVC>:
    /permissive /W4 /WX>)
set_property(TARGET main PROPERTY CXX_STANDARD 11)

# Set up unit testing
add_executable(tests)
target_sources(tests PRIVATE "src/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2)
set_property(TARGET main PROPERTY CXX_STANDARD 11)

include(CTest)
include(Catch)
catch_discover_tests(tests)

# Smoke test
enable_testing()
add_test(NAME Runs COMMAND main)
