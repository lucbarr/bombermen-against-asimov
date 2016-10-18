#include "agent.h"
#include <iostream>

Agent::Agent(const Vec2d pos, const int id){
  id_ = id;
  bombs_ = BOMBS_INIT;
  has_bombs_ = true;
  is_dead_ = false;
  if (pos.isValid()) {
    pos_ = pos;
  } else {
    std::cerr << "[AGENT #" << id_ << "]"; //TODO: macro this
    std::cerr << "ERROR: trying to initialize agent in invalid position." << std::endl;
    pos_ = NULL_POS;
  }
}

// This one is tricky, yet the first&only solution I've found.
// An Intel must try to place bombs on map based on the gamestate.
// It should check for bombs availability before trying to place them,
// but if it doesn't, the method performs a check for placing bombs.
// If is a valid position, it returns a 2D vector (current agent position)
// of where the bomb must be. If not, it returns a null position telling
// it has no bombs to be place. This is tricky because gamestate update must
// take this information of NULL_POS into account.

#if 0
Vec2d Agent::placeBomb(){
  if(has_bombs_){
    bombs_--;
  if (bombs_ <= 0){
    has_bombs_ = false;
    bombs_ = 0;
  }
    return pos_;
  } else {
    std::cerr << "[AGENT #" << id_ << "]";
    std::cerr << "ERROR: trying to place a bomb while not having bombs." << std::endl;
    return NULL_POS;
  }
}
#endif

// TODO: define recharging turns number interval
void Agent::bombRecharge(){
  if (bombs_ < 0){
    bombs_ = 0;
  }
  bombs_++;
  if (!has_bombs_){
    has_bombs_ = true;
  }
}

