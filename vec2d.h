#pragma once

struct Vec2d {
  Vec2d();
  Vec2d(const int a, const int b);
  bool isValid() const ;
  int x,y;
};

