#include "game.h"
#include "gui.h"

#include "AIs/halpp.h"
#include "AIs/dumb.h"
#include "AIs/debug.h"

#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

bool MENU() {
  string input;
  getline (cin, input);
  if (!input.compare("1")){
    return true;
  } else if (!input.compare("0")) {
    cout << "Bye!!" << endl;
    return false;
  } else {
    cout << "Invalid option. Try again." << endl;
    return MENU();
  }
}


int main(){
  Game game;
  DumbBot dumb1, dumb2;
  Debug debug1;
  game.linkIntel(&debug1);
  game.linkIntel(&dumb2);
  //cout << "Insert 1 for stepping forward on the game and 0 to exit:" << endl;
  // create the window
  sf::RenderWindow window(sf::VideoMode(COLUMNS*32, ROWS*32), "Bombermen! Against Asimov");

  // define the level with an array of tile indices
  
  // create the tilemap from the level definition
  TileMap map;
  if (!map.load("tileset.png", sf::Vector2u(32, 32), game.getLevel(), COLUMNS, ROWS))
    return -1;
  Sprite player1("man-indigo.png", 1, 1);
  Sprite player2("man-dusky.png", 0, 0);
  while (!game.isOver()) {// && MENU()){
    game.printMap();
    game.step();
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    // draw the map
    window.clear();
    window.draw(map);
    window.draw(player1);
    window.draw(player2);
    window.display();
  }
  return 0;
}
