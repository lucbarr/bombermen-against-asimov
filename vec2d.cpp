#include "vec2d.h"
#include <iostream>

Vec2d::Vec2d() {
  x = 0;
  y = 0;
}

Vec2d::Vec2d(const int a, const int b){
  x = a;
  y = b;
}

bool Vec2d::isValid() const {
  if(x >= 0 && y >= 0){
    return true;
  } else {
    return false;
  }
}

void Vec2d::debug(){
  std::cerr << "[x: " << x << ", y: " << y << " ]" << std::endl;
}

