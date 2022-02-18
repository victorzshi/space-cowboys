#pragma once

#include <assert.h>

#include <vector>

#include "../components/physics.h"
#include "../components/transform.h"
#include "services/locator.h"

class BulletSystem {
 public:
  BulletSystem() : start(0), active(0), physics(nullptr), transform(nullptr) {}

  int start;
  int active;
  int end;

  Physics* physics;
  Transform* transform;

  void activateBullet(Vector2 position) {
    if (active > end) return;

    // Set bullet position...

    int id = active;
    transform[id].position = position;

    //Physics tempPhysics = physics[active];
    //physics[active] = physics[id];
    //physics[id] = tempPhysics;

    //Transform tempTransform = transform[active];
    //transform[active] = transform[id];
    //transform[id] = tempTransform;

    active++;
  }

  void deactivateBullet(int id) {
    Locator::logger().print("Deactivating bullet ID:");
    Locator::logger().print(std::to_string(id));

    assert(id < active);

    active--;

    // Swap...

    Physics tempPhysics = physics[active];
    physics[active] = physics[id];
    physics[id] = tempPhysics;

    Transform tempTransform = transform[active];
    transform[active] = transform[id];
    transform[id] = tempTransform;
  }

  void update() {
    for (int id = start; id < active; id++) {
      transform[id].position += physics[id].velocity;
      physics[id].updateCollider(transform[id].position);
    }

    for (int id = start; id < active; id++) {
      if (isOutOfBounds(physics[id].collider)) {
        deactivateBullet(id);
      }
    }
  }

  void render(SDL_Renderer* renderer) {
    for (int id = start; id < active; id++) {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawRect(renderer, &physics[id].collider);
    }
  }

 private:
  bool isOutOfBounds(SDL_Rect rect) {
    int topLeftX = rect.x;
    int topLeftY = rect.y;
    int bottomRightX = rect.x + rect.w;
    int bottomRightY = rect.y + rect.h;

    return topLeftX < 0 || topLeftY < 0 || bottomRightX > 1280 ||
           bottomRightY > 720;
  }
};
