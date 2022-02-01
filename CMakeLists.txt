cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(main)

# Dependencies via vcpkg.cmake
find_package(SDL2 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Compile with very strict warning level
add_executable(main)
target_sources(main PRIVATE src/main.cpp)

if(UNIX AND NOT APPLE)
  target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
elseif(WIN32 OR APPLE)
  target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(main PRIVATE /permissive /W4)
endif()

# Set up unit testing
add_executable(tests)
target_sources(tests PRIVATE "src/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(tests)

# Smoke test
enable_testing()
add_test(NAME Runs COMMAND main)
