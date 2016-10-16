#include "block.h"
#include <iostream>

using namespace std;

Block::Block(Vec2d pos, Block_type type){
  if(!pos.isValid()){
    cerr << "[BLOCK]";
    cerr << "ERROR: trying to generate block in invalid position" << std::endl;
  }
  pos_ = pos;
  type_ = type;
}

Block::Block(int x, int y, Block_type type){
  pos_.x = x;
  pos_.y = y;
  type_ = type;
}

void Block::bomb(){
  switch(type_){
    case(FREE):
      break;
    case(BREAKABLE):
      type_ = FREE;
      break;
    case(UNBREAKABLE):
      break;
  }
}
