# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(main VERSION 0.1.2)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dependencies via vcpkg.cmake
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2-image CONFIG REQUIRED)
find_package(SDL2-ttf CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Main target
add_executable(main)
target_sources(main PRIVATE 
  "src/ecs/pools/aliens/aliens.cc"
  "src/ecs/pools/bullets/bullets.cc"
  "src/ecs/pools/explosions/explosions.cc"
  "src/ecs/pools/particles/particles.cc"
  "src/ecs/pools/tanks/tanks.cc"
  "src/ecs/pools/zappers/zappers.cc"
  "src/ecs/pools/pool.cc"
  "src/ecs/systems/input_ai/input_ai.cc"
  "src/ecs/systems/input_player/input_player.cc"
  "src/ecs/systems/render_collider/render_collider.cc"
  "src/ecs/systems/render_sprite/render_sprite.cc"
  "src/ecs/systems/update_aliens/update_aliens.cc"
  "src/ecs/systems/update_effects/update_effects.cc"
  "src/ecs/systems/update_hit/update_hit.cc"
  "src/ecs/systems/update_position/update_position.cc"
  "src/ecs/systems/update_tanks/update_tanks.cc"
  "src/ecs/ecs.cc"
  "src/game/game.cc"
  "src/vector2/vector2.cc"
  "src/main.cc" 
)
target_include_directories(main PRIVATE "src")
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image SDL2::SDL2_ttf)

# Manually link X11 library on Linux
if(UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
  target_include_directories(main PRIVATE ${X11_INCLUDE_DIR})
  target_link_libraries(main PRIVATE ${X11_LIBRARIES})
endif()

# Set strict warning level and all warnings as errors
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(main PRIVATE 
    /permissive 
    /W4 
    /WX
  )
else()
  target_compile_options(main PRIVATE 
    -Wall 
    -Wextra 
    -Wpedantic 
    -Werror 
    -Wno-c++98-compat
  )
endif()

# Define DEBUG macro
target_compile_definitions(main PUBLIC "$<$<CONFIG:DEBUG>:DEBUG>")

# Tests target
add_executable(tests)
target_sources(tests PRIVATE 
  "src/vector2/vector2.cc"
  "src/vector2/vector2.test.cc"
)
target_include_directories(tests PRIVATE "src")
target_link_libraries(tests PRIVATE Catch2::Catch2)

# Add unit tests
include(CTest)
include(Catch)
catch_discover_tests(tests)

# Smoke test
enable_testing()
add_test(NAME "Smoke test" COMMAND main "--smoke-test")

# Configure installer
install(TARGETS main DESTINATION "bin/src")
install(FILES 
  "${PROJECT_BINARY_DIR}/SDL2.dll" 
  "${PROJECT_BINARY_DIR}/SDL2_image.dll" 
  "${PROJECT_BINARY_DIR}/SDL2_ttf.dll" 
  "${PROJECT_BINARY_DIR}/freetype.dll" 
  "${PROJECT_BINARY_DIR}/libpng16.dll" 
  "${PROJECT_BINARY_DIR}/zlib1.dll" 
  "${PROJECT_BINARY_DIR}/bz2.dll" 
  "${PROJECT_BINARY_DIR}/brotlidec.dll" 
  "${PROJECT_BINARY_DIR}/brotlicommon.dll" 
  DESTINATION "bin/src"
)
install(DIRECTORY data DESTINATION ".")

set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION "bin/src")
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_NAME "space-cowboys")
include(CPack)
