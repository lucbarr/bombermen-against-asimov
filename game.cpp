#include "game.h"
#include <iostream>
#include <random>

#define IS_CORNER(i,j) ((i==1 && j==1) || (i==1 && j==2) || (i==2 && j ==1) \
       || (i==(ROWS-2) && j==1) || (i==(ROWS-2) && j==2) || (i==(ROWS-3) && j==1) \
       || (i==1 && j==(COLUMNS-2)) || (i==2 && j==(COLUMNS-2)) || (i==1 && (j==COLUMNS-3)) \
       || (i==(ROWS-2) && j==(COLUMNS-2)) || (i==(ROWS-2) && j==(COLUMNS-3)) || (i==(ROWS-3) && j==(COLUMNS-2)))

using namespace std;

Game::Game() : last_id_(0){
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
  for (int i = 0; i < map.size() ; ++i){
    for (int j = 0 ; j < map[0].size(); ++j){
      char aux;
      bool block_flag = true;
      for (auto agent : agents_){
        if (agent.getPos() == map[i][j].getPos()){
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

void Game::step() {
  vector<Command> commands;
  vector<Vec2d> exploded_path;
  // Runs all bombs internal clocks.
  this->bombstep();
  // Loop for reading intel commands.
#if 0
  for (auto intel : intels_){
    Command command;
    command = intel->sendCommand();
    commands.push_back(command);
  }
#endif
  // NOTE: Agents position in vector corresponds to intel's as well
  // Loop for adding set bombs.
  for (int i = 0 ; i < commands.size() ; ++i){
    if(commands[i].set_bomb){
      bombs_.push_back(Bomb(agents_[i].getPos()));
    }
  }
  // Loop for finding exploded bombpath.
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
          exploded_path.push_back(Vec2d(centre_x+r, centre_y));
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
      bombs_.erase(bombs_.begin()+i);
    }
  }
}

void Game::linkIntel(Intel* intel){
  static int intel_counter = 1;
  static Vec2d corner(1,1); 
  last_id_ = intel_counter;
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

