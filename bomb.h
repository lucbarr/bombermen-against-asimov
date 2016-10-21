#pragma once

#include "vec2d.h"

const int DEFAULT_TIMER = 3;
const int DEFAULT_RANGE = 3;

class Bomb {
public:
  Bomb(Vec2d pos);
  Bomb() = delete;
  ~Bomb() = default;
  Bomb& operator= (const Bomb&) = default;

  void tick(); // Runs bomb's internal clock.
  bool isBoom();

  Vec2d getPos() const { return pos_; }
  int getTimer() const { return timer_; };
  int getRange() const { return range_; }
  char getBombSymbol() const { return symbol_bomb_; }
  char getExplosionSymbol() const { return symbol_explosion_; }

private:
  Vec2d pos_;
  int timer_;
  int range_;
  char symbol_bomb_ = 'o';
  char symbol_explosion_ = 'X';
};

