#pragma once

#include <vector>
#include "block.h"
#include "intel.h"
#include "agent.h"
#include "bomb.h"
#include "gamestate.h"

const int ROWS = 13;
const int COLUMNS = 17;
// Chance on generating breakable block at map initialization:
const float F_B_RATIO = 0.7f; 
typedef std::vector< std::vector<Block> > Map;

class Intel;

// Game is a class for management of game state based on
// the interaction of each entity with the Map and with one another.
class Game{
public:
  Game();
  ~Game() = default ;
  // Game map of blocks displacement
  Map map;

  // Performs a step in game time:
  // Manages to perform all entities a step in time
  // and process these changes in the game state.
  void step();
  // Prints Map, deciding what overlays what.
  void printMap();
  // Adds an Intel to the game.
  void linkIntel(Intel*);
  bool isOver() const { return gameover; }
private:
  bool gameover;
  // Methods for performing each entities step in time
  void bombstep();
  void agentstep();
  Vec2d move(MOVE movement);
  // Containers for games entities
  std::vector<Intel*> intels_;
  std::vector<Agent> agents_;
  std::vector<Bomb> bombs_;
};

