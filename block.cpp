#include "block.h"
#include <iostream>

using namespace std;

Block::Block(const Vec2d pos, const Block_type type){
  if(!pos.isValid()){
    cerr << "[BLOCK]";
    cerr << "ERROR: trying to generate block in invalid position" << std::endl;
  }
  pos_ = pos;
  type_ = type;
}

Block::Block(const int x, const int y, const Block_type type){
  pos_.x = x;
  pos_.y = y;
  type_ = type;
}

void Block::crush(){
  if (type_ == BREAKABLE){
    type_ = FREE;
  }
}

