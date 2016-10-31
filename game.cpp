#include "game.h"
#include "intel.h"
#include <iostream>
#include <random>
#include <algorithm>

#define IS_CORNER(i,j) ((i==1 && j==1) || (i==1 && j==2) || (i==2 && j ==1) \
       || (i==(ROWS-2) && j==1) || (i==(ROWS-2) && j==2) || (i==(ROWS-3) && j==1) \
       || (i==1 && j==(COLUMNS-2)) || (i==2 && j==(COLUMNS-2)) || (i==1 && (j==COLUMNS-3)) \
       || (i==(ROWS-2) && j==(COLUMNS-2)) || (i==(ROWS-2) && j==(COLUMNS-3)) || (i==(ROWS-3) && j==(COLUMNS-2)))

using namespace std;

Game::Game() : gameover(false){
  random_device rd;
  mt19937 mt(rd());
  uniform_real_distribution<float> rand(0, 1);
  // Generates standand map without breakable blocks.
  for (int i = 0; i < ROWS; ++i){
    for (int j = 0; j < COLUMNS; ++j){
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
  for (int i = 0; i < ROWS; ++i){
    for (int j = 0 ; j < COLUMNS; ++j){
      bool block_flag = true;
      char aux;
      auto it = find(exploded_path_.begin(), exploded_path_.end(), Vec2d(i,j));
      // "Rendering" overlaying sequence, the last one
      // overlays the other previous, if existing.
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
      if (it != exploded_path_.end()) {
        aux = SYMBOL_EXPLOSION;
        block_flag = false;
      }
      if (block_flag){
        switch (map[i][j].getType()){
          case FREE:
            aux = ' ';
            break;
          case BREAKABLE:
            aux = '+';
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

Vec2d Game::move(Move movement){
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
  // Runs all bombs and agents internal clocks.
  this->bombstep();
  this->agentstep();

  // COMMENT(naum): Melhor criar uma função só para serializar o gamestate
  // (diminui o tamanho da função step e fica mais claro o que está acontecendo)
  Gamestate gamestate;

  // Packing gamestate
  gamestate.mapHeight = ROWS;
  gamestate.mapWidth  = COLUMNS;

  for (auto bomb : bombs_) {
    BombEntity bombEntity;
    bombEntity.id      = 0;
    bombEntity.pos     = bomb.getPos();
    bombEntity.timer   = bomb.getTimer();
    bombEntity.range   = bomb.getRange();
    bombEntity.ownerId = 0;

    gamestate.bombs.push_back(bombEntity);
  }

  for (auto agent : agents_) {
    AgentEntity agentEntity;
    agentEntity.id    = agent.getId();
    agentEntity.pos   = agent.getPos();
    agentEntity.bombs = agent.getBombs();

    gamestate.agents.push_back(agentEntity);
  }

  for (int i = 0; i < ROWS; ++i){
    for (int j = 0; j < COLUMNS; ++j){
      gamestate.blocks[i][j] = map[i][j].getType();
    }
  }

  // Loop for reading intels commands.
  for (int i = 0; i < (int)intels_.size() ; ++i) {
    gamestate.selfId = agents_[i].getId();
    commands.push_back(intels_[i]->sendCommand(gamestate));
  }

  // NOTE: Agents position in vector corresponds to intel's as well
  // Loop for adding set bombs.
  for (int i = 0 ; i < (int)commands.size() ; ++i) {
    // COMMENT(naum): A lógica de adicionar as bombas no vetor era para estar dentro do agente
    // O que você fez foi transferir a lógica que era para ser do agente para o step do Game
    // Assim você tá verificando mais de uma vez coisas como hasBombs
    if (commands[i].placeBomb && agents_[i].hasBombs()) {
      bombs_.push_back(Bomb { agents_[i].getPos(), agents_[i].getId() });
      agents_[i].placeBomb();
    }
  }

  // Loop for finding exploded bombpath.
  // NOTE: can have repeated elements in vector.
  vector<Bomb> new_bombs;
  for (int i = 0; i < (int)bombs_.size() ; ++i){
    // COMMENT(naum): É importante o tamanho do nome da variável ser relativo a quanto você
    // vai usar. Se você está dentro de um loop de bombas dá pra saber que x e y é a posição
    // da bomba. Então não precisa criar nome grande
    const int x = bombs_[i].getPos().x;
    const int y = bombs_[i].getPos().y;
    const int range = bombs_[i].getRange();
    if (bombs_[i].isBoom()){
      exploded_path_.push_back(bombs_[i].getPos());

      // COMMENT(naum): Não precisa desses 4 for iguais
      /*
      for (int r = 1; r <= range; ++r ){
        if (map[centre_x+r][centre_y].getType() != FREE){
          map[centre_x+r][centre_y].crush();
          break;
        } else {
          exploded_path_.push_back(Vec2d(centre_x+r, centre_y));
        }
      }
      for (int r = -1; r >= -range; --r ){
        if (map[centre_x+r][centre_y].getType() != FREE){
          map[centre_x+r][centre_y].crush();
          break;
        } else {
          exploded_path_.push_back(Vec2d(centre_x+r, centre_y));
        }
      }
      for (int r = 1; r <= range; ++r ){
        if (map[centre_x][centre_y+r].getType() != FREE){
          map[centre_x][centre_y+r].crush();
          break;
        } else {
          exploded_path_.push_back(Vec2d(centre_x, centre_y+r));
        }
      }
      for (int r = -1; r >= -range; --r ){
        if (map[centre_x][centre_y+r].getType() != FREE){
          map[centre_x][centre_y+r].crush();
          break;
        } else {
          exploded_path_.push_back(Vec2d(centre_x, centre_y+r));
        }
      }
      */

      // COMMENT(naum): 4 direções
      const int dx[] = { 1, -1, 0,  0 };
      const int dy[] = { 0,  0, 1, -1 };

      for (int i = 0; i < 4; ++i) { // COMMENT(naum): for para as 4 direções
        for (int r = 1; r <= range; ++r) {
          const int ex = x + r * dx[i],
                    ey = y + r * dy[i];
          const auto type = map[ex][ey].getType();

          map[x+r][y].crush(); // COMMENT(naum): Já tem o if do tipo dentro da função crush, então basta chamar que ela só vai destruir o bloco se for BREAKABLE
          if (type != UNBREAKABLE)
            exploded_path_.push_back(Vec2d(ex, ey));
          if (type != FREE) break;
        }
      }
    } else {
      new_bombs.push_back(bombs_[i]);
    }
  }
  bombs_ = new_bombs;

  // Loop for checking deaths
  // COMMENT(naum): Tem como otimizar isso, mas como são poucos agentes e o terreno não é grande não vai ser problema
  for (auto &agent : agents_){
    auto it = find(exploded_path_.begin(), exploded_path_.end(), agent.getPos());
    if (it != exploded_path_.end()){
      agent.kill();
    }
  }

  // Loop for finding and moving alive agents
  vector<Agent> alive_agents;
  for (int i = 0 ; i < (int)agents_.size() ; ++i){
    if (!agents_[i].isDead()){
      alive_agents.push_back(agents_[i]);
      // COMMENT(naum): future é algo conhecido de concorrência, não é um bom nome pq pode ser confuso
      // COMMENT(naum): move é uma função muito usada da STL. É bom evitar esse nome tb.
      Vec2d future = agents_[i].getPos() + move(commands[i].move);
      if (map[future.x][future.y].getType() == FREE){
        agents_[i].setPos(future);
      }
    }
  }

  if (alive_agents.size() == 0){
    cout << "It's a tie!! Everyone is dead!!" << endl;
    this->printMap();
    gameover = true;
  } else if (alive_agents.size() == 1) {
    cout << "We have a winner!" << endl;
    this->printMap();
    gameover = true;
  }
}

void Game::linkIntel(Intel* intel){
  // COMMENT(naum): Essas variáveis static são ruins para o código. Isso faz com que você
  // só consiga rodar uma vez. É melhor pensar em uma forma de linkar intel e poder reiniciar
  // o contador para poder rodar de novo (como se fosse um jogo mesmo)
  static int intel_counter = 1;
  static Vec2d corner(1,1);
  //intel->setId(intel_counter);
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

