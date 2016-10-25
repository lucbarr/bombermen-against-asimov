#pragma once

#include <vector>

#include "block.h"

typedef std::vector< std::vector<Block_type> > Blockmap;

struct Gamestate{
  std::vector<Vec2d> bombs;
  std::vector<Vec2d> agents;
  Blockmap blocks;
  Vec2d self;
};

