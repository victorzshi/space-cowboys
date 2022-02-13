#include "services/locator.h"
#include "world/world.h"

int main(int argc, char *argv[]) {
  Locator::initialize();

  bool isSmokeTest = false;
  if (argc == 2 && std::string(argv[1]) == "--smoke-test") {
    isSmokeTest = true;
  }

  World world = World();

  if (world.initialize()) {
    world.run(isSmokeTest);
  }

  world.terminate();

  return 0;
}
