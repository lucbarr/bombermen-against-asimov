#include "game.h"
#include "AIs/halpp.h"
#include <string>
#include <iostream>

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
  Intel* intel1;
  Intel* intel2;
  Halpp halpp1;
  Halpp halpp2;
  intel1 = &halpp1;
  intel2 = &halpp2;
  game.linkIntel(intel1);
  game.linkIntel(intel2);
  cout << "Insert 1 for stepping forward on the game and 0 to exit:" << endl;
  while (!game.isOver() && MENU()){
    game.printMap();
    game.step();
  }
  return 0;
}
