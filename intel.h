#pragma once

#include "game.h"

class Intel {

public:
  virtual void step(Game&) = 0;
  virtual void setBomb(Game&) = 0;
};

