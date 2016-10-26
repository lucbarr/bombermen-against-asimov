#pragma once
#include "../intel.h"

class DumbBot : public Intel {
public:
  virtual Command sendCommand(const Gamestate /*gameState*/) {
    Command command;
    command.placeBomb = 0;
    command.move = HALT;
    return command;
  }
};
