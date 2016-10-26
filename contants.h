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

struct Gamestate {
  std::vector<Vec2d> bombs;
  std::vector<Vec2d> agents;
  std::array<std::array<BlockType, COLUMNS>, ROWS> blocks;
  Vec2d self;
  int mapWidth, mapHeight;
};


// Definition of Command data structure.
struct Command {
  Move move;
  bool placeBomb; // COMMENT(naum): Nome melhor
};
