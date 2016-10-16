#pragma once

#include "vec2d.h"

enum Block_type{
  FREE,
  BREAKABLE,
  UNBREAKABLE
};

class Block{
public:
  Block() = default;
  ~Block() = default;
  Block(const Vec2d pos, const Block_type type);
  Block(const int x, const int y, const Block_type type);

  void bomb();

  Block_type getType() const { return type_; }
  Vec2d getPos() const { return pos_; }
private:
  Vec2d pos_;
  Block_type type_;
};

