#include "game/game.h"
#include "services/locator.h"

int main(int argc, char *argv[]) {
  Locator::initialize();

  bool isSmokeTest = false;
  if (argc == 2 && std::string(argv[1]) == "--smoke-test") {
    isSmokeTest = true;
  }

  Game game = Game();

  if (game.initialize()) {
    game.run(isSmokeTest);
  }

  game.terminate();

  return 0;
}
