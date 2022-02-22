#include "game/game.h"

int main(int argc, char *argv[]) {
  printf("Program start...\n");

  bool isSmokeTest = false;
  if (argc == 2 && std::string(argv[1]) == "--smoke-test") {
    printf("Smoke testing...\n");
    isSmokeTest = true;
  }

  Game game = Game();

  if (game.initialize()) {
    game.run(isSmokeTest);
  }

  game.terminate();

  return 0;
}
