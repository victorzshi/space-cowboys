#include "game/game.hpp"
#include "services/locator.hpp"
#include "services/logging/debug_logging.hpp"

int main(int argc, char *argv[]) {
  DebugLogging *debugLogging = new DebugLogging();
  Locator::provide(debugLogging);

  Logging *logging = Locator::getLogging();
  logging->print("Warning: Debug mode is on");

  bool isSmokeTest = false;

  if (argc == 2 && std::string(argv[1]) == "--smoke-test") {
    logging->print("Smoke testing...");

    isSmokeTest = true;
  }

  if (Game::init()) {
    Game game = Game(isSmokeTest);
    game.start();
    game.stop();
  }

  return 0;
}
