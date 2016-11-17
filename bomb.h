#pragma once

#include "constants.h"
#include "vec2d.h"

class Bomb {
public:
  static const char symbol_bomb_ = 'o';

  Bomb(const Vec2d pos, const int ownedId) : pos_ { pos }, ownedId_ { ownedId } {}
  Bomb() = delete;

  void  tick()                { timer_--; }
  void  chain()               { timer_ = 0; }
  bool  isBoom()        const { return timer_ <= 0; }

  Vec2d getPos()        const { return pos_; }
  int   getTimer()      const { return timer_; };
  int   getRange()      const { return range_; }
  char  getBombSymbol() const { return symbol_bomb_; }

private:
  Vec2d pos_;
  int ownedId_;
  int timer_ = BOMB_DEFAULT_TIMER;
  int range_ = BOMB_DEFAULT_RANGE;
};

