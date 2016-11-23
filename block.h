#pragma once

#include "constants.h"
#include "vec2d.h"

// Block class defines what is a block object in the game map.
class Block{
public:
  Block() = default;
  // Overloaded constructors for easing operations
  Block(const int x, const int y, const BlockType type) :
      pos_ { x, y }, type_ { type }
  {}

  // Crushs a breakable block.
  void crush() { if (type_ == BREAKABLE) type_ = FREE; }

  BlockType getType() const { return type_; }
  Vec2d getPos() const { return pos_; }
private:
  Vec2d pos_;
  BlockType type_;
};

