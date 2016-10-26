#pragma once

#include "vec2d.h"

const int DEFAULT_TIMER = 3;
const int DEFAULT_RANGE = 2;

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
  int timer_        = DEFAULT_TIMER;
  int range_        = DEFAULT_RANGE;
  char symbol_bomb_ = 'o';
};

