#include "update_hit.h"

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/timer.h"
#include "ecs/components/transform.h"
#include "ecs/engine.h"
#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"
#include "ecs/pools/explosions/explosions.h"
#include "ecs/pools/particles/particles.h"
#include "ecs/pools/tanks/tanks.h"
#include "ecs/pools/zappers/zappers.h"
#include "services/locator.h"

void UpdateHit::update(Engine& e) {
  updateBullets(e);
  updateZappers(e);
}

void UpdateHit::updateBullets(Engine& e) {
  Collider* collider = e.collider();

  Aliens& aliens = e.aliens();
  Bullets& bullets = e.bullets();

  int beginBullets = bullets.begin();
  int beginAliens = aliens.begin();

  for (int i = beginBullets; i < bullets.size(); i++) {
    if (e.isOutOfBoundsTop(collider[i].box)) {
      bullets.deactivate(i);

      continue;
    }

    for (int j = beginAliens; j < aliens.size(); j++) {
      if (collider[i].isHit(collider[j].box)) {
        explodeAlien(e, j);

        bullets.deactivate(i);
        aliens.deactivate(j);

        break;
      }
    }
  }
}

void UpdateHit::updateZappers(Engine& e) {
  Collider* collider = e.collider();

  Tanks& tanks = e.tanks();
  Zappers& zappers = e.zappers();

  int beginTanks = tanks.begin();
  int beginZappers = zappers.begin();

  for (int i = beginZappers; i < zappers.size(); i++) {
    if (e.isOutOfBoundsBottom(collider[i].box)) {
      zappers.deactivate(i);

      continue;
    }

    for (int j = beginTanks; j < tanks.size(); j++) {
      if (collider[i].isHit(collider[j].box)) {
        explodeTank(e, j);

        zappers.deactivate(i);
        tanks.deactivate(j);

        break;
      }
    }
  }
}

void UpdateHit::explodeAlien(Engine& e, int index) {
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  Explosions& explosions = e.explosions();
  Particles& particles = e.particles();

  Uint64 current = SDL_GetTicks64();

  int id = explosions.size();
  if (explosions.activate(id)) {
    transform[id].position = transform[index].position;
    collider[id].box = collider[index].box;
    timer[id].previous = current;
  }

  for (int i = 0; i < 3; i++) {
    id = particles.size();
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

void UpdateHit::explodeTank(Engine& e, int index) {
  Collider* collider = e.collider();
  Timer* timer = e.timer();
  Transform* transform = e.transform();

  Explosions& explosions = e.explosions();

  Uint64 current = SDL_GetTicks64();

  int id = explosions.size();
  if (explosions.activate(id)) {
    transform[id].position = transform[index].position;

    collider[id].box.w = 144;
    collider[id].box.h = 144;
    collider[id].update(transform[id].position);

    timer[id].previous = current;
  }
}
