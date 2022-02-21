#include "update_effects.h"

#include <SDL.h>

#include "ecs/components/physics.h"
#include "ecs/components/timer.h"
#include "ecs/engine.h"
#include "ecs/pools/explosions/explosions.h"
#include "ecs/pools/particles/particles.h"

void UpdateEffects::update(Engine& e) {
  Physics* physics = e.physics();
  Timer* timer = e.timer();

  Explosions& explosions = e.explosions();
  Particles& particles = e.particles();

  Uint64 current = SDL_GetTicks64();

  Uint64 duration = explosions.DURATION;
  int begin = explosions.begin();
  for (int i = begin; i < explosions.size(); i++) {
    if (timer[i].elapsed(current) >= duration) {
      explosions.deactivate(i);
    }
  }

  duration = particles.DURATION;
  begin = particles.begin();
  for (int i = begin; i < particles.size(); i++) {
    if (timer[i].elapsed(current) >= duration) {
      particles.deactivate(i);
    } else {
      physics[i].acceleration = Vector2(0.0f, 0.5f);  // Simulate gravity
    }
  }
}
