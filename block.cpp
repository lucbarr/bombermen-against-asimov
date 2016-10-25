#include "block.h"
#include <iostream>

using namespace std;

Block::Block(const int x, const int y, const BLOCK_TYPE type){
  pos_.x = x;
  pos_.y = y;
  type_ = type;
}

void Block::crush(){
  if (type_ == BREAKABLE){
    type_ = FREE;
  }
}

