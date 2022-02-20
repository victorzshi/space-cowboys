#include "input_ai.h"

#include "ecs/components/ai.h"
#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"

void InputAI::input(Engine& e) {
  AI* ai = e.ai();
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Transform* transform = e.transform();

  int begin = e.aliens().begin();
  int size = e.aliens().size();

  for (int i = begin; i < size; i++) {
    if (ai[i].isPathEnd) {
      ai[i].isPathEnd = false;

      ai[i].prevDirection = ai[i].nextDirection;
      ai[i].nextDirection = Direction::DOWN;

      // TODO(Victor): Need a better way to account for the grid gutter.
      ai[i].goalHeight +=
          static_cast<float>(collider[i].box.h + collider[i].box.h / 4);
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
  }
}
