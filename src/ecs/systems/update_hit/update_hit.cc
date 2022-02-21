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

  Aliens& aliens = e.aliens();
  Bullets& bullets = e.bullets();

  int beginBullets = bullets.begin();
  int beginAliens = aliens.begin();

  for (int i = beginBullets; i < bullets.size(); i++) {
    if (e.isOutOfBounds(collider[i].box)) {
      bullets.deactivate(i);

      continue;
    }

    for (int j = beginAliens; j < aliens.size(); j++) {
      if (collider[i].isHit(collider[j].box)) {
        createExplosion(e, j);

        bullets.deactivate(i);
        aliens.deactivate(j);

        break;
      }
    }
  }
}

void UpdateHit::createExplosion(Engine& e, int index) {
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  Particles& particles = e.particles();

  Uint64 current = SDL_GetTicks64();

  for (int i = 0; i < 3; i++) {
    int id = particles.size();
    if (particles.activate(id)) {
      float x = e.random(-5.0f, 5.0f);
      float y = e.random(-5.0f, 5.0f);
      physics[id].acceleration = Vector2(x, y);
      physics[id].velocity = Vector2(x, y);
      transform[id].position = transform[index].position;
      collider[id].update(transform[id].position);
      timer[id].previous = current;
    }
  }
}
