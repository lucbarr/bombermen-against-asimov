#include "game.h"
#include "gui.h"

#include "AIs/halpp.h"
#include "AIs/dumb.h"
#include "AIs/debug.h"

#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, const char* argv[]){
  bool debug;
  for (int i = 0; i < argc; i++){
    if (string(argv[i]) == "-d" || string(argv[i]) == "--debug") { debug = true; }
    else { debug = false; }
  }
  Game game;
  DumbBot dumb1, dumb2;
  Debug debug1;
  if (debug) { game.linkIntel(&debug1); }
  else { game.linkIntel(&dumb1); }
  game.linkIntel(&dumb2);
  //cout << "Insert 1 for stepping forward on the game and 0 to exit:" << endl;
  // create the window
  sf::RenderWindow window(sf::VideoMode(COLUMNS*32, ROWS*32), "Bombermen! Against Asimov");
  debug::Window debugw(window.getPosition(), window.getSize());
  if (!debug){
    debugw.window.close();
  }
  // create the tilemap from the level definition
  TileMap map;
  if (!map.load("assets/tileset.png", sf::Vector2u(32, 32), game.getLevel(), COLUMNS, ROWS))
    return -1;
  // Load player sprites
  Sprite player1("assets/man-indigo.png", 0, 0, 32, 32);
  Sprite player2("assets/man-dusky.png", 1, 0, 32, 32);
  Sprite bomb("assets/bomb.png", 0 , 0,32,32);
  while (!game.isOver()) {
    player1.update(game.getAgentPos(0).x, game.getAgentPos(0).y);
    player2.update(game.getAgentPos(1).x, game.getAgentPos(1).y);
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
    if(debug){
      while (debugw.window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
          debugw.window.close();
      }
    }
    // draw the map
    window.clear();
    window.draw(map);
    window.draw(player1);
    window.draw(player2);
    if(debug){
      debugw.window.display();
      debugw.draw();
    }
    game.printMap();
    for ( auto bomb_sprite : bomb_sprites ){
      window.draw(bomb_sprite);
    }
    window.display();
    // console printing and gamme interaction step
    if(debug){
      debugw.in();
      debug1.setDebugCommand(debugw.getMove(), debugw.getBomb());
    }
    game.step();
    map.update(game.getLevel());
    // TODO: refactor this ugly thing
  }
  return 0;
}

