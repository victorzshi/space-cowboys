//#pragma once
//
//#include "ecs/ecs.h"
//
// class UpdateBulletPosition {
// public:
//  static void update(ECS& ecs) {
//    // Active* active = ecs.active;
//    Transform* transform = ecs.transform;
//    Physics* physics = ecs.physics;
//
//    // for (size_t i = 0; i < ecs.bulletIds.size(); i++) {
//    //   int id = ecs.bulletIds[i];
//
//    //  if (active[id].isNotActive()) continue;
//
//    //  transform[id].position += physics[id].velocity;
//    //  physics[id].updateCollider(transform[id].position);
//
//    //  if (ecs.isOutOfBounds(physics[id].collider)) {
//    //    active[id].state = false;
//    //  }
//    //}
//
//
//    for (int id = ecs.bulletStart; id < ecs.bulletActive; id++) {
//      transform[id].position += physics[id].velocity;
//      physics[id].updateCollider(transform[id].position);
//    }
//
//    //for (int id = ecs.bulletActive; id >= ecs.bulletStart; id--) {
//    //  if (ecs.isOutOfBounds(physics[id].collider)) {
//    //    ecs.deactivateBullet(id);
//    //  }
//    //}
//  }
//};
