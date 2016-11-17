#pragma once

#include "constants.h"

// Intel is a base class for an AI to perform in game.
// see AIs/README.md for further information
class Intel {
public:
  // Alleged to send commands so Game can perform them.
  // Must be redefined for each derived from Intel class.
  virtual Command sendCommand(const Gamestate) = 0;

};

