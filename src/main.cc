#include "game/game.h"

int main(int argc, char *argv[]) {
  printf("Pro tip: You can touch the aliens without dying.\n\n");

  const char *text =
      "  ()     __   __    _    , __  _    __                        \n"
      "  /\\    /  ` /  `  ' )  / / ')' )  /                         \n"
      " /  )  /--  /--     /  / /  /  /  /                           \n"
      "/__/__(___,(___,   (__/_(__/  (__/                            \n"
      "                    //                                        \n"
      "                   (/                                         \n"
      "  ()   _ __  __   __  __      __  __  _     ___    __  _    , \n"
      "  /\\  ' )  )/  ) /  )/  `    /  )/ ')' )   //  )  / ')' )  / \n"
      " /  )  /--'/--/ /   /--     /   /  /  / / //--<  /  /  /  /   \n"
      "/__/__/   /  (_(__/(___,   (__/(__/  (_(_//___/_(__/  (__/_ooo\n"
      "                                                       //     \n"
      "                                                      (/      \n";

  printf("%s", text);

  bool isSmokeTest = false;
  if (argc == 2 && std::string(argv[1]) == "--smoke-test") {
    isSmokeTest = true;
  }

  Game game = Game();

  if (game.initialize()) {
    game.run(isSmokeTest);
  } else {
    fprintf(stderr, "Game could not initialize.\n");
  }

  game.terminate();

  return 0;
}
