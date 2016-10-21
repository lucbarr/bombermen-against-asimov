#include "bomb.h"
#include <iostream>

using namespace std;

Bomb::Bomb(const Vec2d pos) : pos_(pos), timer_(DEFAULT_TIMER), range_(DEFAULT_RANGE) {

}

// Returns a bool telling if bomb explodes or not after game iteration
void Bomb::tick(){
  timer_--;
}

bool Bomb::isBoom(){
  return (timer_ <= 0);
}
