#pragma once
#include "vec2d.h"

class Agent {
public:
  Agent() = delete;
  Agent(const Vec2d pos, const int id);

  void kill() { is_dead_ = true; }

  Vec2d getPos() const { return pos_; }
  int getId() const { return id_; }
  int getBombs() const { return bombs_; }
  bool hasBombs() const { return has_bombs_; }
  void bombRecharge();

private:
  int bombs_;
  int id_;
  bool has_bombs_;
  bool is_dead_;
  Vec2d pos_;
};

const int BOMBS_INIT = 3;
const Vec2d NULL_POS (-1,-1);
