#include "halpp.h"

Halpp::Halpp(const Game& game) : id_(game.getLastId()) {

}

Command Halpp::sendCommand() {
  Command command;
  command.set_bomb = true;
  command.move = NORTH;
}

