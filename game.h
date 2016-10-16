#pragma once

#include <vector>
#include "block.h"

const int ROWS = 13;
const int COLUMNS = 17;
typedef std::vector< std::vector<Block> > Map;

class Game{
public:
  Game(); 
  ~Game() = default ;
  Map map;
private:
};

