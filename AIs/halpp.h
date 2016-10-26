#pragma once
#include "../intel.h"
// Hal++ is an allegedly better than HAL9001 AI.

class Halpp : public Intel{
public:
  virtual Command sendCommand(const Gamestate) override {
    Command command;
    command.placeBomb = true;
    command.move = SOUTH;
    return command;
  }
};
