#pragma once

// Vectorial 2d definition to ease positioning
// management within the game.

struct Vec2d {
  Vec2d();
  Vec2d(const int a, const int b);
  bool isValid() const ;
  int x,y;
  void debug();
};

inline bool operator==(Vec2d a, Vec2d b){
  return (a.x == b.x && a.y == b.y);
}
