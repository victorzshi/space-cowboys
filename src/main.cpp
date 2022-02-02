#include <iostream>
#include <string>

#include "game/game.hpp"

int main(int argc, char* argv[]) {
  bool isSmokeTest = false;

  if (argc == 2 && std::string(argv[1]) == "--smoke-test") {
    std::cout << "Smoke testing..." << std::endl;
    isSmokeTest = true;
  }

  if (Game::init()) {
    Game game = Game(isSmokeTest);
    game.start();
    game.stop();
  }

  return 0;
}
