#include "halpp.h"

Command Halpp::sendCommand() {
  Command command;
  command.set_bomb = true;
  command.move = NORTH;
  return command;
}

