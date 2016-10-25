#pragma once

#include <vector>

#include "block.h"

typedef std::vector< std::vector<BLOCK_TYPE> > Blockmap;

struct Gamestate{
  std::vector<Vec2d> bombs;
  std::vector<Vec2d> agents;
  Blockmap blocks;
  Vec2d self;
  int map_width, map_height;
};

