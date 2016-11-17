#pragma once

#include <vector>
#include <array>
#include "vec2d.h"

// Constants

const int BOMB_DEFAULT_TIMER = 3;
const int BOMB_DEFAULT_RANGE = 2;

const int ROWS = 13;
const int COLUMNS = 17;

// Enums

enum BlockType {
  FREE,
  BREAKABLE,
  UNBREAKABLE
};

enum Move {
  NORTH,
  SOUTH,
  EAST,
  WEST,
  HALT
};

// Structs

struct Entity {
  int id;    
  Vec2d pos; // Entity position
};

struct BombEntity : public Entity {
  int ownerId; 
  int timer;   // Ticks left to explosion
  int range;   // Explosion range
};

struct AgentEntity : public Entity {
  int bombs; // Number of bombs available
  //int score; // Could de added in a near future
};

struct Gamestate {
  std::vector<BombEntity>  bombs;
  std::vector<AgentEntity> agents;
  std::array<std::array<BlockType, COLUMNS>, ROWS> blocks;
  //Vec2d self;
  int selfId;  
  int mapWidth, mapHeight;
};


// Definition of Command data structure.
struct Command {
  Move move;
  bool placeBomb; 
};
