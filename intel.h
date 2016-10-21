#pragma once

#include "game.h"

enum MOVE{
  NORTH,
  SOUTH,
  EAST,
  WEST,
  HALT
};

struct Command{
  MOVE move;
  bool set_bomb;
};

class Intel {

public:
  virtual Command sendCommand() = 0;
  void setId(int id) { id_ = id; }
private:
  int id_;
};

