#pragma once

#include "contants.h"
#include "vec2d.h"

// COMMENT(naum): Classe muito simples para precisar de .cpp

class Bomb {
public:
  Bomb(const Vec2d pos) : pos_ { pos } {}
  Bomb() = delete;

  void  tick()                { timer_--; }
  bool  isBoom()        const { return timer_ <= 0; }

  Vec2d getPos()        const { return pos_; }
  int   getTimer()      const { return timer_; };
  int   getRange()      const { return range_; }
  char  getBombSymbol() const { return symbol_bomb_; }

private:
  Vec2d pos_;
  int timer_        = BOMB_DEFAULT_TIMER;
  int range_        = BOMB_DEFAULT_RANGE;
  char symbol_bomb_ = 'o';
};

