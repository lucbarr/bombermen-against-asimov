#include "agent.h"
#include <iostream>

Agent::Agent(const Vec2d pos, const int id){
  clock_ = RECHARGE_TIME;
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

#if 1
void Agent::placeBomb(){
  if(has_bombs_){
    bombs_--;
  if (bombs_ == 0){
    has_bombs_ = false;
  }
  } else {
    std::cerr << "[AGENT #" << id_ << "]";
    std::cerr << "WARNING: trying to place a bomb while not having bombs." << std::endl;
  }
}
#endif

// TODO: define recharging turns number interval
void Agent::bombRecharge(){
  if(clock_ == 0){
    bombs_++;
    if (!has_bombs_){
      has_bombs_ = true;
    }
    clock_ = RECHARGE_TIME;
  } else if (bombs_ < BOMBS_INIT){
    clock_--;
  }
}

