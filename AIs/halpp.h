#pragma once
#include "../intel.h"
// Hal++ is an allegedly better than HAL9001 AI.

class Halpp : public Intel{
public:
  virtual Command sendCommand(const Gamestate);
private:
  int id_;
};
