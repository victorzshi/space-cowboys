# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(main)

# Dependencies via vcpkg.cmake
find_package(SDL2 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# main target
add_executable(main)
target_sources(main PRIVATE 
  "src/main.cpp" 
  "src/game/game.cpp"
  "src/services/logging/debug_logging.cpp"
  "src/services/locator.cpp"
)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Manually link X11 library on Linux
if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  target_include_directories(main PRIVATE ${X11_INCLUDE_DIR})
  target_link_libraries(main PRIVATE ${X11_LIBRARIES})
endif()

# Compile with very strict warning level
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-c++98-compat)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-c++98-compat)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror -Wno-c++98-compat)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(main PRIVATE /permissive /W4 /WX)
endif()

# tests target
add_executable(tests)
target_sources(tests PRIVATE 
  "src/game/game.test.cpp"
)
target_link_libraries(tests PRIVATE Catch2::Catch2)

# Add unit tests
include(CTest)
include(Catch)
catch_discover_tests(tests)

# Smoke test
enable_testing()
add_test(NAME "Smoke test" COMMAND main "--smoke-test")