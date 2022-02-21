#include "update_hit.h"

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"
#include "ecs/pools/particles/particles.h"
#include "services/locator.h"

void UpdateHit::update(Engine& e) {
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  Aliens& aliens = e.aliens();
  Bullets& bullets = e.bullets();
  Particles& particles = e.particles();

  Uint64 current = SDL_GetTicks64();

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
          physics[particle].acceleration = Vector2(-3.0f, 0.0f);
          physics[particle].velocity = Vector2(-3.0f, 0.0f);
          transform[particle].position = transform[j].position;
          collider[particle].update(transform[particle].position);
          timer[particle].previous = current;
        }

        particle += 1;
        if (particles.activate(particle)) {
          physics[particle].acceleration = Vector2(0.0f, -3.0f);
          physics[particle].velocity = Vector2(0.0f, -3.0f);
          transform[particle].position = transform[j].position;
          collider[particle].update(transform[particle].position);
          timer[particle].previous = current;
        }

        particle += 1;
        if (particles.activate(particle)) {
          physics[particle].acceleration = Vector2(3.0f, 0.0f);
          physics[particle].velocity = Vector2(3.0f, 0.0f);
          transform[particle].position = transform[j].position;
          collider[particle].update(transform[particle].position);
          timer[particle].previous = current;
        }

        bullets.deactivate(i);
        aliens.deactivate(j);

        break;
      }
    }
  }
}
