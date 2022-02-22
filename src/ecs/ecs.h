#pragma once

#include <SDL.h>

#include "ecs/components/sprite.h"
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

  virtual void initialize(SDL_Renderer* renderer, const Uint8* keyboard,
                          SDL_Rect& viewport) override;
  virtual void terminate() override;

  virtual SDL_Renderer* renderer() override;
  virtual const Uint8* keyboard() override;
  virtual SDL_Rect& viewport() override;
  virtual Screen screen() override;

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

  virtual void setScreen(Screen screen) override;

  virtual int createEntity() override;
  virtual void updateActive() override;

  virtual Sprite createSpriteFromFile(std::string file) override;
  virtual Sprite createSpriteFromText(std::string text, int fontSize) override;
  virtual bool isOutOfBounds(SDL_Rect rect) override;
  virtual bool isOutOfBoundsWidth(SDL_Rect rect) override;
  virtual bool isOutOfBoundsTop(SDL_Rect rect, int offset) override;
  virtual bool isOutOfBoundsBottom(SDL_Rect rect, int offset) override;
  virtual float random(float min, float max) override;

  virtual void input() override;
  virtual void update() override;
  virtual void render(float delay) override;

 private:
  static const int MAX_ENTITIES = 5000;

  int id_;

  SDL_Renderer* renderer_;
  const Uint8* keyboard_;
  SDL_Rect viewport_;
  Screen screen_;

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

  Sprite title_;
  Sprite subtitle_;
  Sprite text_;

  void initializePools();
  void initializeText();
  void restart();
};
