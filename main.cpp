#include "game.h"
#include "gui.h"

#include "AIs/halpp.h"
#include "AIs/dumb.h"
#include "AIs/debug.h"

#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

int main(){
  Game game;
  DumbBot dumb1, dumb2;
  Debug debug1;
  game.linkIntel(&debug1);
  game.linkIntel(&dumb2);
  //cout << "Insert 1 for stepping forward on the game and 0 to exit:" << endl;
  // create the window
  sf::RenderWindow window(sf::VideoMode(COLUMNS*32, ROWS*32), "Bombermen! Against Asimov");
  // create the tilemap from the level definition
  TileMap map;
  if (!map.load("assets/tileset.png", sf::Vector2u(32, 32), game.getLevel(), COLUMNS, ROWS))
    return -1;
  // Load player sprites
  Sprite player1("assets/man-indigo.png", 1, 1);
  Sprite player2("assets/man-dusky.png", 0, 0);
  Sprite bomb("assets/bomb.png", 0 , 0);
  while (!game.isOver()) {
    vector<Sprite> bomb_sprites;
    auto bomb_pos = game.getBombsPos();
    for ( auto pos : bomb_pos ) {
      bomb_sprites.push_back(bomb);
      bomb_sprites.back().update(pos.x, pos.y);
    }
    sf::Event event;
    while (window.pollEvent(event)) {
      if(event.type == sf::Event::Closed)
        window.close();
    }
    // draw the map
    window.clear();
    window.draw(map);
    window.draw(player1);
    window.draw(player2);
    for ( auto bomb_sprite : bomb_sprites ){
      window.draw(bomb_sprite);
    }
    window.display();
    // console printing and gamme interaction step
    game.printMap();
    game.step();
    map.update(game.getLevel());
    // TODO: refactor this ugly thing
    player1.update(game.getAgentPos(0).x, game.getAgentPos(0).y);
    player2.update(game.getAgentPos(1).x, game.getAgentPos(1).y);

  }
  return 0;
}
