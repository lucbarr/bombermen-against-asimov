#pragma once

#include <vector>
#include <array>
#include "constants.h"
#include "block.h"
#include "agent.h"
#include "bomb.h"

// Chance on generating breakable block at map initialization:
const float F_B_RATIO = 0.7f;
const char  SYMBOL_EXPLOSION = 'X';

class Intel;

// Game is a class for management of game state based on
// the interaction of each entity with the Map and with one another.
class Game{
public:
  Game();
  // Game map of blocks displacement
  std::array< std::array<Block, COLUMNS>, ROWS> map; // COMMENT(naum): Should probably change this name 

  int* getLevel() { return level_tilemap_; }
  Vec2d getAgentPos(int id) { return agents_[id].getPos(); }
  std::vector<Vec2d> getBombsPos();
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
  int* level_tilemap_;
  void updateTilemap();
  Vec2d move(Move movement);
  // Containers for games entities
  std::vector<Intel*> intels_;
  std::vector<Agent> agents_;
  std::vector<Bomb> bombs_;
  // Container for printing bomb explosions purposes
  std::vector<Vec2d> exploded_path_;
};

