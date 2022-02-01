file(GLOB_RECURSE SRC_FILES src/*.[ch]pp)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(clang-format COMMAND clang-format -i -style=file ${SRC_FILES})
endif()
