#pragma once
#include "intel.h"
// Hal++ is an allegedly better than HAL9001 AI.

class Halpp : public Intel{
public:
  virtual void step(Map&);
  virtual void setBomb(Map&);
};
