#include "halpp.h"

Command Halpp::sendCommand(const Gamestate gamestate) {
  Command command;
  command.set_bomb = true;
  command.move = SOUTH;
  return command;
}

