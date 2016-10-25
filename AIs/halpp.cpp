#include "halpp.h"
#include <iostream>

Command Halpp::sendCommand(const Gamestate gamestate) {
  Command command;
  command.set_bomb = true;
  command.move = SOUTH;
  std::cout << gamestate.blocks[1][1] << std::endl;
  return command;
}

