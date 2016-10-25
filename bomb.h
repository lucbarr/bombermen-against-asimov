#pragma once

#include "vec2d.h"

const int DEFAULT_TIMER = 3;
const int DEFAULT_RANGE = 2;

class Bomb {
public:
  Bomb(const Vec2d pos);
  Bomb() = delete;
  ~Bomb() = default;
  Bomb& operator= (const Bomb&) = default;

  void tick(); // Runs bomb's internal clock.
  bool isBoom();

  Vec2d getPos() const { return pos_; }
  int getTimer() const { return timer_; };
  int getRange() const { return range_; }
  char getBombSymbol() const { return symbol_bomb_; }

private:
  Vec2d pos_;
  int timer_;
  int range_;
  char symbol_bomb_ = 'o';
};

