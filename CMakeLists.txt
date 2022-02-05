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
  "src/services/locator.cpp"
  "src/services/logging/debug_logging/debug_logging.cpp"
  "src/services/logging/release_logging/release_logging.cpp"
)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Manually link X11 library on Linux
if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  target_include_directories(main PRIVATE ${X11_INCLUDE_DIR})
  target_link_libraries(main PRIVATE ${X11_LIBRARIES})
endif()

# Set strict warning level and all warnings as errors
if(MSVC)
  target_compile_options(main PRIVATE /W4 /WX)
else()
  target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Define DEBUG macro
target_compile_definitions(main PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

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