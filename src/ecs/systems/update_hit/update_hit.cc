#include "update_hit.h"

#include "ecs/components/collider.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"
#include "ecs/pools/particles/particles.h"
#include "services/locator.h"

void UpdateHit::update(Engine& e) {
  Collider* collider = e.collider();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  Aliens& aliens = e.aliens();
  Bullets& bullets = e.bullets();
  Particles& particles = e.particles();

  Uint64 previous = SDL_GetTicks64();

  int beginBullets = bullets.begin();
  int beginAliens = aliens.begin();

  for (int i = beginBullets; i < bullets.size(); i++) {
    if (e.isOutOfBounds(collider[i].box)) {
      bullets.deactivate(i);

      continue;
    }

    for (int j = beginAliens; j < aliens.size(); j++) {
      if (collider[i].isHit(collider[j].box)) {
        int particle = particles.size();
        if (particles.activate(particle)) {
          transform[particle].position = transform[j].position;
          timer[particle].previous = previous;
        }

        bullets.deactivate(i);
        aliens.deactivate(j);

        break;
      }
    }
  }
}
