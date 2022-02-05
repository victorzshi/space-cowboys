#include "game/game.hpp"
#include "services/locator.hpp"

int main(int argc, char *argv[]) {
  bool isSmokeTest = false;
  if (argc == 2 && std::string(argv[1]) == "--smoke-test") {
    isSmokeTest = true;
  }

  if (Game::initialize()) {
    Game game = Game(isSmokeTest);
    game.start();
    game.stop();
  }

  return 0;
}
