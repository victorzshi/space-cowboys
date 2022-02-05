#include "game/game.h"
#include "service/locator.h"

int main(int argc, char *argv[]) {
  Locator::initialize();

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
