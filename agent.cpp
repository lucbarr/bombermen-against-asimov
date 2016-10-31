#include "agent.h"
#include <iostream>

Agent::Agent(const Vec2d pos, const int id){
  clock_ = RECHARGE_TIME;
  id_ = id;
  bombs_ = BOMBS_INIT;
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
  // COMMENT(naum): Nessa função que devia ter a lógica de adicionar a bomba na lista de bombas

  if(hasBombs()){
    bombs_--;
  } else {
    std::cerr << "[AGENT #" << id_ << "]";
    std::cerr << "WARNING: trying to place a bomb while not having bombs." << std::endl;
  }
}
#endif

// COMMENT(naum): Bomberman original tinha só uma contagem de bombas que
//                o jogador podia colocar. Quando uma bomba explodia o jogador
//                ganhava de volta a bomba

// TODO: define recharging turns number interval
void Agent::bombRecharge(){
  if(clock_ == 0){
    bombs_++;
    clock_ = RECHARGE_TIME;
  } else if (bombs_ < BOMBS_INIT){
    clock_--;
  }
}

