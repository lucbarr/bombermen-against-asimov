#include "game.h"
#include <iostream>
#include <random>
#include <algorithm>

#define IS_CORNER(i,j) ((i==1 && j==1) || (i==1 && j==2) || (i==2 && j ==1) \
       || (i==(ROWS-2) && j==1) || (i==(ROWS-2) && j==2) || (i==(ROWS-3) && j==1) \
       || (i==1 && j==(COLUMNS-2)) || (i==2 && j==(COLUMNS-2)) || (i==1 && (j==COLUMNS-3)) \
       || (i==(ROWS-2) && j==(COLUMNS-2)) || (i==(ROWS-2) && j==(COLUMNS-3)) || (i==(ROWS-3) && j==(COLUMNS-2)))

using namespace std;

Game::Game() : gameover(false){
  map = Map(ROWS, vector<Block>(COLUMNS));
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<float> rand(0, 1);
  // Generates standand map without breakable blocks.
  for (int i = 0; i < map.size() ; ++i){
    for (int j = 0; j < map[0].size() ; ++j){
      const float r_num = rand(mt);
      if (i == 0 || i == (ROWS-1) || j == 0 || j==(COLUMNS-1)){
        map[i][j] = Block(i,j,UNBREAKABLE);
      } else if ((IS_CORNER(i,j))){ //Corners must be free
        map[i][j] = Block(i,j,FREE); 
      } else if (i%2 || j%2) {
        if (r_num > F_B_RATIO){
          map[i][j] = Block(i,j,FREE);
        } else {
          map[i][j] = Block(i,j,BREAKABLE);
        }
      }
      else {
        map[i][j] = Block(i,j,UNBREAKABLE);
      }
    }
  }
}

// NOTE for the future: adapt for sprite overlay
void Game::printMap(){
  vector<Vec2d> bombs_pos;
  for (auto bomb : bombs_){
    bombs_pos.push_back(bomb.getPos());
  }
  for (int i = 0; i < map.size() ; ++i){
    for (int j = 0 ; j < map[0].size(); ++j){
      char aux;
      bool block_flag = true;
      for (auto bomb_pos : bombs_pos){
        if (bomb_pos == map[i][j].getPos()){
          aux = bombs_[0].getBombSymbol();
          block_flag = false;
          break;
        }
      }
      for (auto agent : agents_){
        if (agent.getPos() == map[i][j].getPos() && !agent.isDead()){
          aux = '0' + agent.getId();
          block_flag = false;
          break;
        }
      }
      if (block_flag){
        switch (map[i][j].getType()){
          case FREE:
            aux = ' ';
            break;
          case BREAKABLE:
            aux = '%';
            break;
          case UNBREAKABLE:
            aux = '#';
            break;
        }
      }
      cout << aux ;
    }
    cout << endl ;
  }
}

void Game::bombstep(){
  for (auto &bomb : bombs_ ){
    bomb.tick();
  }
}

void Game::agentstep(){
  for (auto &agent : agents_) {
    agent.bombRecharge();
  }
}

Vec2d Game::move(MOVE movement){
  switch (movement){
    case NORTH:
      return Vec2d(-1,0);
    case SOUTH:
      return Vec2d(1,0);
    case EAST:
      return Vec2d(0,1);
    case WEST:
      return Vec2d(0,-1);
    case HALT:
      return Vec2d(0,0);
  }
}

void Game::step() {
  vector<Command> commands;
  vector<Vec2d> exploded_path;
  // Runs all bombs and agents internal clocks.
  this->bombstep();
  this->agentstep();
  // Loop for reading intels commands.
  for (auto intel : intels_){
    commands.push_back(intel->sendCommand());
  }
  // NOTE: Agents position in vector corresponds to intel's as well
  // Loop for adding set bombs.
  for (int i = 0 ; i < commands.size() ; ++i){
    if(commands[i].set_bomb && agents_[i].hasBombs()){
      bombs_.push_back(Bomb(agents_[i].getPos()));
      agents_[i].placeBomb();
    }
  }

  // Loop for finding exploded bombpath.
  // NOTE: can have repeated elements in vector.
  vector<Bomb> new_bombs;
  for (int i = 0; i < bombs_.size() ; ++i){
    const int centre_x = bombs_[i].getPos().x;
    const int centre_y = bombs_[i].getPos().y;
    const int range = bombs_[i].getRange();
    if (bombs_[i].isBoom()){
      exploded_path.push_back(bombs_[i].getPos());
      for (int r = 1; r <= range; ++r ){
        if (map[centre_x+r][centre_y].getType() != FREE){
          map[centre_x+r][centre_y].crush();
          break;
        } else {
          exploded_path.push_back(Vec2d(centre_x+r, centre_y));
        }
      }
      for (int r = -1; r >= -range; --r ){
        if (map[centre_x+r][centre_y].getType() != FREE){
          map[centre_x+r][centre_y].crush();
          break;
        } else {
          exploded_path.push_back(Vec2d(centre_x+r, centre_y));
        }
      }
      for (int r = 1; r <= range; ++r ){
        if (map[centre_x][centre_y+r].getType() != FREE){
          map[centre_x][centre_y+r].crush();
          break;
        } else {
          exploded_path.push_back(Vec2d(centre_x, centre_y+r));
        }
      }
      for (int r = -1; r >= -range; --r ){
        if (map[centre_x][centre_y+r].getType() != FREE){
          map[centre_x][centre_y+r].crush();
          break;
        } else {
          exploded_path.push_back(Vec2d(centre_x, centre_y+r));
        }
      }
    } else {
      new_bombs.push_back(bombs_[i]);
    }
  }
  bombs_ = new_bombs;
  // Loop for checking deaths
  for (auto &agent : agents_){
    auto it = find(exploded_path.begin(), exploded_path.end(), agent.getPos());
    if (it != exploded_path.end()){
      agent.kill();
    }
  }
  // Loop for finding and moving alive agents
  vector<Agent> alive_agents;
  for (int i = 0 ; i < agents_.size() ; ++i){
    if (!agents_[i].isDead()){
      alive_agents.push_back(agents_[i]);
      Vec2d future = agents_[i].getPos() + move(commands[i].move);
      if (map[future.x][future.y].getType() == FREE){
        agents_[i].setPos(future);
      }
    }
  }
  if (alive_agents.size() == 0){
    cout << "It's a tie!! Everyone is dead!!" << endl;
    gameover = true;
  } else if (alive_agents.size() == 1 ) {
    cout << "We have a winner!" << endl;
  }
}

void Game::linkIntel(Intel* intel){
  static int intel_counter = 1;
  static Vec2d corner(1,1); 
  intel->setId(intel_counter);
  intels_.push_back(intel);
  agents_.push_back(Agent(corner, intel_counter));
  //Switch spawning position of agents
  switch(intel_counter){
    case (1):
      corner = Vec2d(ROWS-2,COLUMNS-2);
      break;
    case (2):
      corner = Vec2d(1,COLUMNS-2);
      break;
    case (3):
      corner = Vec2d(ROWS-2,1);
      break;
    case (4):
      corner = Vec2d(1,1);
      cerr << "[WARNING]: max number of players reached" << endl;
      break;
  }
  intel_counter++;
}

