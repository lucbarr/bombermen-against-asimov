#include "vec2d.h"

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
