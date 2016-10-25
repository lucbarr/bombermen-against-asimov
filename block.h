#pragma once

#include "vec2d.h"

enum BLOCK_TYPE{
  FREE,
  BREAKABLE,
  UNBREAKABLE
};

// Block class defines what is a block object in the game map.
class Block{
public:
  Block() = default;
  ~Block() = default;
  // Overloaded constructors for easing operations
  Block(const int x, const int y, const BLOCK_TYPE type);

  // Crushs a breakable block.
  void crush();

  BLOCK_TYPE getType() const { return type_; }
  Vec2d getPos() const { return pos_; }
private:
  Vec2d pos_;
  BLOCK_TYPE type_;
};

