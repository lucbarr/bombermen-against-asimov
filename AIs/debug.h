#pragma once

#include "../intel.h"
#include <iostream>

using namespace std;

class Debug : public Intel {
public:
  virtual Command sendCommand(const Gamestate) override {
    cerr << "[DEBUG] SENT COMMAND: MOVE: " << command.move << " BOMB: " << command.placeBomb << endl;
    return command;
  }
  Debug(){
    cerr << "[DEBUG]: " << "YOU'VE ENTERED DEBUG MODE, please follow the debugging protocol:" << endl;
    cerr << "INSERT TWO CHARS, SEPARATED BY SPACE IN SEQUENCE:" << endl << "SETBOMB? : 'y' or 'n'"  << " <space> "<< "ARROWS : 'w' 'a' 's' 'd'" << endl;
  }
  Move moveIn(char c){
    switch(c){
      case 'w':
        return NORTH;
      case 'a':
        return WEST;
      case 's':
        return SOUTH;
      case 'd':
        return EAST;
      default:
        return HALT;
    }
  }
  bool bombIn(char c){
    return c=='y'? true : false;
  }
  void setDebugCommand(char move, char bomb){
    command.placeBomb = bombIn(bomb);
    command.move = moveIn(move);
    cerr << "[DEBUG] SET COMMAND: MOVE: " << move << " BOMB: " << bomb << endl;
  }
  Command command;

};
