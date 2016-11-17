#pragma once

#include "../intel.h"
#include <iostream>

using namespace std;

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

class Debug : public Intel {
public:
  virtual Command sendCommand(const Gamestate) override {
    char move,bomb;
    cin >> move >> bomb ;
    Command command;
    command.placeBomb = bombIn(move);
    command.move = moveIn(bomb);
    return command;
  }
  Debug(){
    cerr << "[DEBUG]: " << "YOU'VE ENTERED DEBUG MODE, please follow the debugging protocol:" << endl;
    cerr << "INSERT TWO CHARS, SEPARATED BY SPACE IN SEQUENCE:" << endl << "SETBOMB? : 'y' or 'n'"  << " <space> "<< "ARROWS : 'w' 'a' 's' 'd'" << endl;
  }

};
