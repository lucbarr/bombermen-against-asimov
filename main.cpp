#include "game.h"
#include "intel.h"
#include "AIs/halpp.h"

int main(){
  Game game;
  Intel* intel1;
  Intel* intel2;
  Halpp halpp1(game);
  Halpp halpp2(game);
  intel1 = &halpp1;
  intel2 = &halpp2;
  game.linkIntel(intel1);
  game.linkIntel(intel2);
  game.printMap();
  return 0;
}
