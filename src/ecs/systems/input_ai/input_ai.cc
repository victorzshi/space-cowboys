#include "input_ai.h"

#include <SDL.h>

#include "ecs/components/ai.h"
#include "ecs/components/physics.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/zappers/zappers.h"
#include "services/locator.h"

void InputAI::input(Engine& e) {
  AI* ai = e.ai();
  Physics* physics = e.physics();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  Aliens& aliens = e.aliens();

  Uint64 cooldown = aliens.ZAPPER_COOLDOWN;

  Uint64 current = SDL_GetTicks64();

  int begin = aliens.begin();
  int size = aliens.size();
  for (int i = begin; i < size; i++) {
    // Update direction
    if (ai[i].isPathEnd) {
      ai[i].isPathEnd = false;

      ai[i].prevDirection = ai[i].nextDirection;
      ai[i].nextDirection = Direction::DOWN;

      ai[i].goalHeight += static_cast<float>(aliens.WIDTH + aliens.GUTTER);
    }

    if (ai[i].nextDirection == Direction::DOWN &&
        transform[i].position.y >= ai[i].goalHeight) {
      ai[i].nextDirection = ai[i].prevDirection == Direction::LEFT
                                ? Direction::RIGHT
                                : Direction::LEFT;
      ai[i].prevDirection = Direction::DOWN;
    }

    float deltaVelocity = e.aliens().DELTA_VELOCITY;
    switch (ai[i].nextDirection) {
      case Direction::LEFT:
        physics[i].velocity.x = -deltaVelocity;
        physics[i].velocity.y = 0.0f;
        break;
      case Direction::RIGHT:
        physics[i].velocity.x = deltaVelocity;
        physics[i].velocity.y = 0.0f;
        break;
      case Direction::DOWN:
        physics[i].velocity.x = 0.0f;
        physics[i].velocity.y = deltaVelocity;
        break;
    }

    // Shoot zapper
    if (timer[i].elapsed(current) >= cooldown) {
      float random = e.random(0.0f, 1.0f);
      if (random > 0.9999f) {
        int id = e.zappers().size();
        if (e.zappers().activate(id)) {
          transform[id].position = transform[i].position;

          timer[i].previous = current;
        }
      }
    }
  }
}
