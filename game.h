#pragma once

#include <vector>
#include "block.h"

const int ROWS = 13;
const int COLUMNS = 17;
const float F_B_RATIO = 0.7f; //Chance on generating breakable block at map initialization.
typedef std::vector< std::vector<Block> > Map;

class Game{
public:
  Game(); 
  ~Game() = default ;
  Map map;

  void printMap();
private:
};

