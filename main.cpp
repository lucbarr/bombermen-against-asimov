#include "game.h"

#include "AIs/halpp.h"
#include "AIs/dumb.h"
#include "AIs/debug.h"

#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

bool MENU() {
  string input;
  getline (cin, input);
  if (!input.compare("1")){
    return true;
  } else if (!input.compare("0")) {
    cout << "Bye!!" << endl;
    return false;
  } else {
    cout << "Invalid option. Try again." << endl;
    return MENU();
  }
}


int main(){
  Game game;
  DumbBot dumb1, dumb2;
  Debug debug1;
  game.linkIntel(&debug1);
  game.linkIntel(&dumb2);
  //cout << "Insert 1 for stepping forward on the game and 0 to exit:" << endl;
  while (!game.isOver()) {// && MENU()){
    game.printMap();
    game.step();
  }
  return 0;
}
