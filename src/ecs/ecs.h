#pragma once

#include <SDL.h>

#include <random>

#include "ecs/pools/aliens/aliens.h"
#include "ecs/pools/bullets/bullets.h"
#include "ecs/pools/explosions/explosions.h"
#include "ecs/pools/particles/particles.h"
#include "ecs/pools/tanks/tanks.h"
#include "ecs/pools/zappers/zappers.h"
#include "engine.h"

class ECS : public Engine {
 public:
  ECS();

  virtual void initialize(SDL_Renderer* renderer, SDL_Rect& viewport,
                          const Uint8* keyboard) override;
  virtual void terminate() override;

  virtual SDL_Renderer* renderer() override;
  virtual SDL_Rect& viewport() override;
  virtual const Uint8* keyboard() override;

  virtual AI* ai() override;
  virtual Collider* collider() override;
  virtual Physics* physics() override;
  virtual Sprite* sprite() override;
  virtual Timer* timer() override;
  virtual Transform* transform() override;

  virtual Active& active() override;
  virtual Aliens& aliens() override;
  virtual Bullets& bullets() override;
  virtual Explosions& explosions() override;
  virtual Particles& particles() override;
  virtual Tanks& tanks() override;
  virtual Zappers& zappers() override;

  virtual int createEntity() override;
  virtual SDL_Texture* createTexture(std::string file) override;
  virtual bool isOutOfBoundsWidth(SDL_Rect rect) override;
  virtual bool isOutOfBoundsTop(SDL_Rect rect) override;
  virtual bool isOutOfBoundsBottom(SDL_Rect rect) override;
  virtual void updateActive() override;
  virtual float random(float min, float max) override;

  virtual void input() override;
  virtual void update() override;
  virtual void render(float delay) override;

 private:
  static const int MAX_ENTITIES = 3000;

  int id_;

  SDL_Renderer* renderer_;
  SDL_Rect viewport_;
  const Uint8* keyboard_;

  AI* ai_;
  Collider* collider_;
  Physics* physics_;
  Sprite* sprite_;
  Timer* timer_;
  Transform* transform_;

  Active active_;
  Aliens aliens_;
  Bullets bullets_;
  Explosions explosions_;
  Particles particles_;
  Tanks tanks_;
  Zappers zappers_;
};
