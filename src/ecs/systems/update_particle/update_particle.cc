#include "update_particle.h"

#include <SDL.h>

#include "ecs/components/timer.h"
#include "ecs/engine.h"
#include "ecs/pools/particles/particles.h"

void UpdateParticle::update(Engine& e) {
  Timer* timer = e.timer();

  Particles& particles = e.particles();

  Uint64 current = SDL_GetTicks64();
  Uint64 duration = particles.DURATION;

  int begin = particles.begin();

  for (int i = begin; i < particles.size(); i++) {
    if (timer[i].elapsed(current) >= duration) {
      particles.deactivate(i);
    }
  }
}
