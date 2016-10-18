#pragma once

#include "game.h"
#include "vec2d.h"

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

class Game;

class Intel {

public:
  virtual Command sendCommand() = 0;
private:
  int id_;
};

