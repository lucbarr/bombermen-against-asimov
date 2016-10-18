#pragma once
#include "../intel.h"
// Hal++ is an allegedly better than HAL9001 AI.

class Halpp : public Intel{
public:
  Halpp(const Game&);
  virtual Command sendCommand() override;
private:
  int id_;
};
