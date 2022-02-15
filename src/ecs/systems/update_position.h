#pragma once

#include "ecs/ecs.h"

class UpdatePosition {
 public:
  static void update(ECS& ecs) {
    Physics* physics = ecs.physics();
    Transform* transforms = ecs.transforms();

    for (int i = 0; i < ecs.size(); i++) {
      physics[i].velocity = physics[i].velocity + physics[i].acceleration;

      transforms[i].position = transforms[i].position + physics[i].velocity;

      if (transforms[i].position.y < 0) {
        transforms[i].position.y = 720;
      } else if (transforms[i].position.y > 720) {
        transforms[i].position.y = 0;
      }

      if (transforms[i].position.x < 0) {
        transforms[i].position.x = 1280;
      } else if (transforms[i].position.x > 1280) {
        transforms[i].position.x = 0;
      }
    }
  }
};
