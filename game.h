#pragma once

#include <vector>
#include "block.h"
#include "intel.h"
#include "agent.h"

const int ROWS = 13;
const int COLUMNS = 17;
const float F_B_RATIO = 0.7f; //Chance on generating breakable block at map initialization.
typedef std::vector< std::vector<Block> > Map;

class Intel;

class Game{
public:
  Game(); 
  ~Game() = default ;
  Map map;

  void printMap();
  void linkIntel(Intel*);
  int getLastId() const { return last_id_; }
private:
  std::vector<Intel*> intels_;
  std::vector<Agent> agents_;
  int last_id_;
};

