# Set vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(main LANGUAGES CXX VERSION 0.1.0)

# Find dependencies via vcpkg.cmake
find_package(SDL2 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# main target
add_executable(main)
target_sources(main PRIVATE "src/main.cpp")
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)
set_property(TARGET main PROPERTY CXX_STANDARD 11)

# Compile with very strict warning level
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(main PRIVATE /permissive /W4 /WX)
endif()

# tests target
add_executable(tests)
target_sources(tests PRIVATE "src/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2)
set_property(TARGET main PROPERTY CXX_STANDARD 11)

include(CTest)
include(Catch)
catch_discover_tests(tests)

enable_testing()
add_test(NAME Runs COMMAND main)
