#include "game.h"
#include <iostream>

using namespace std;

Game::Game(){
  map = Map(ROWS, vector<Block>(COLUMNS));
  // Generates standand map without breakable blocks.
  for (int i = 0; i < map.size() ; ++i){
    for (int j = 0; j < map[0].size() ; ++j){
      if (i == 0 || i == (ROWS-1) || j == 0 || j==(COLUMNS-1)){
        map[i][j] = Block(i,j,UNBREAKABLE);
      } else if (j%2 || i%2){
        map[i][j] = Block(i,j,FREE); 
      } else {
        map[i][j] = Block(i,j,UNBREAKABLE);
      }
    }
  }
}

