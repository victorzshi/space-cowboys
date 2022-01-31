#include "game/game.hpp"

int main() {
  if (Game::init()) {
    Game::start();
  } else {
    Game::stop();
  }

  return 0;
}
