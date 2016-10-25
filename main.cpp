#include "game.h"
#include "AIs/halpp.h"
#include <iostream>

int main(){
  char c = 'a';
  Game game;
  Intel* intel1;
  Intel* intel2;
  Halpp halpp1;
  Halpp halpp2;
  intel1 = &halpp1;
  intel2 = &halpp2;
  game.linkIntel(intel1);
  game.linkIntel(intel2);
  while (!game.isOver()){
    game.step();
    game.printMap();
    std::cin >> c;
  }
  return 0;
}
