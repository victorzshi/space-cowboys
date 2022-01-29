#include <iostream>

#include "hello/hello.hpp"

int main() {
  std::cout << Hello::get_greeting();
  return 0;
}
