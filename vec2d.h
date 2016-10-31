#pragma once
#include <iostream>

// Vectorial 2d definition to ease positioning
// management within the game.

struct Vec2d {
  int x,y;

  Vec2d() : x{0}, y{0} {}
  Vec2d(const int a, const int b) : x{a}, y{b} {}

  bool isValid() const { return (x >= 0 && y >= 0); }
  void debug() { std::cerr << "[x: " << x << ", y: " << y << " ]" << std::endl; }

  Vec2d operator-()        { return { -x, -y }; }
  Vec2d operator+(Vec2d v) { return { x+v.x, y+v.y }; }
  Vec2d operator-(Vec2d v) { return { x-v.x, y-v.y }; }
  Vec2d operator*(int s)   { return { s*x, s*y }; }
  bool operator==(Vec2d v) { return x == v.x && y == v.y; }
  bool operator!=(Vec2d v) { return x != v.x || y != v.y; }
};
