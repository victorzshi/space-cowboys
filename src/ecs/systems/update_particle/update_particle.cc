#include "update_particle.h"

#include <SDL.h>

#include "ecs/components/collider.h"
#include "ecs/components/physics.h"
#include "ecs/components/timer.h"
#include "ecs/engine.h"
#include "ecs/pools/particles/particles.h"

void UpdateParticle::update(Engine& e) {
  Collider* collider = e.collider();
  Physics* physics = e.physics();
  Timer* timer = e.timer();

  Particles& particles = e.particles();

  Uint64 current = SDL_GetTicks64();
  Uint64 duration = particles.DURATION;

  int begin = particles.begin();

  for (int i = begin; i < particles.size(); i++) {
    if (e.isOutOfBoundsBottom(collider[i].box) ||
        timer[i].elapsed(current) >= duration) {
      particles.deactivate(i);
    } else {
      physics[i].acceleration = Vector2(0.0f, 0.5f);  // Simulate gravity
    }
  }
}
