#include "game.h"
#include <iostream>
#include <random>

#define IS_CORNER(i,j) ((i==1 && j==1) || (i==1 && j==2) || (i==2 && j ==1) \
       || (i==(ROWS-2) && j==1) || (i==(ROWS-2) && j==2) || (i==(ROWS-3) && j==1) \
       || (i==1 && j==(COLUMNS-2)) || (i==2 && j==(COLUMNS-2)) || (i==1 && (j==COLUMNS-3)) \
       || (i==(ROWS-2) && j==(COLUMNS-2)) || (i==(ROWS-2) && j==(COLUMNS-3)) || (i==(ROWS-3) && j==(COLUMNS-2)))

using namespace std;

Game::Game(){
  map = Map(ROWS, vector<Block>(COLUMNS));
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<float> rand(0, 1);
  // Generates standand map without breakable blocks.
  for (int i = 0; i < map.size() ; ++i){
    for (int j = 0; j < map[0].size() ; ++j){
      const float r_num = rand(mt);
      if (i == 0 || i == (ROWS-1) || j == 0 || j==(COLUMNS-1)){
        map[i][j] = Block(i,j,UNBREAKABLE);
      } else if ((IS_CORNER(i,j))){ //Corners must be free
        map[i][j] = Block(i,j,FREE); 
      } else if (i%2 || j%2) {
        if (r_num > F_B_RATIO){
          map[i][j] = Block(i,j,FREE);
        } else {
          map[i][j] = Block(i,j,BREAKABLE);
        }
      }
      else {
        map[i][j] = Block(i,j,UNBREAKABLE);
      }
    }
  }
}

void Game::printMap(){
  for (int i = 0; i < map.size() ; ++i){
    for (int j = 0 ; j < map[0].size(); ++j){
      char aux;
      switch (map[i][j].getType()){
        case FREE:
          aux = ' ';
          break;
        case BREAKABLE:
          aux = '%';
          break;
        case UNBREAKABLE:
          aux = '#';
          break;
      }
      cout << aux ;
    }
    cout << endl ;
  }
}
