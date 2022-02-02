#include "game/game.hpp"

int main(int argc, char* argv[]) {
  // Ignore unused parameters
  (void)argc;
  (void)argv;






  if (Game::init()) {
    Game game = Game();
    game.start();
    game.stop();
  }

  return 0;
}
