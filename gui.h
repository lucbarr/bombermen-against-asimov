#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
  bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, const int width, const int height) {
    height_ = height;
    width_  = width;
    tileSize_ = tileSize;
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
      return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < width; ++i){
      for (int j = 0; j < height; ++j) {
        // get the current tile number
        int tileNumber = tiles[i + j * width];

        // find its position in the tileset texture
        int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
        int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
        quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
        quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
      }
    }
    return true;
  }
  void update(const int* tiles){
    for (int i = 0; i < width_; ++i){
      for (int j = 0; j < height_; ++j) {
        // get the current tile number
        int tileNumber = tiles[i + j * width_];

        // find its position in the tileset texture
        int tu = tileNumber % (m_tileset.getSize().x / tileSize_.x);
        int tv = tileNumber / (m_tileset.getSize().x / tileSize_.x);

        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[(i + j * width_) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f(i * tileSize_.x, j * tileSize_.y);
        quad[1].position = sf::Vector2f((i + 1) * tileSize_.x, j * tileSize_.y);
        quad[2].position = sf::Vector2f((i + 1) * tileSize_.x, (j + 1) * tileSize_.y);
        quad[3].position = sf::Vector2f(i * tileSize_.x, (j + 1) * tileSize_.y);
        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(tu * tileSize_.x, tv * tileSize_.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize_.x, tv * tileSize_.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize_.x, (tv + 1) * tileSize_.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize_.x, (tv + 1) * tileSize_.y);
      }
    }
  }
  private:
    int width_, height_;
    sf::Vector2u tileSize_;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
      // apply the transform
      states.transform *= getTransform();
      // apply the tileset texture
      states.texture = &m_tileset;
      // draw the vertex array
      target.draw(m_vertices, states);
    }
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

class Sprite : public sf::Sprite {
public:
  Sprite(const std::string& sprite, int j, int i, int width, int height){
    if (!texture_.loadFromFile(sprite, sf::IntRect(0,0,width,height))){
      std::cerr << "[GUI ERROR]: couldn't load sprite file:" << sprite << std::endl;
    } else {
      this->setTexture(texture_);
      this->setPosition(sf::Vector2f(i*width,j*height));
    }
    width_ = width;
    height_ = height;
  }
  void update(int j, int i){
    this->setPosition(sf::Vector2f(i*width_,j*height_));
  }
private:
  sf::Texture texture_;
  int width_, height_;
};

namespace debug{
  class Window;
  enum Arrows{
    ARROWS_ALLUP,
    W_DOWN,
    A_DOWN,
    S_DOWN,
    D_DOWN
  };
  enum BombKeys{
    BOMBS_ALLUP,
    Y_DOWN,
    N_DOWN
  };
}

class debug::Window {
public:
  Window(sf::Vector2i main_window_pos, sf::Vector2u main_window_size) : arrows_(ARROWS_ALLUP), 
             bombkeys_(BOMBS_ALLUP), 
             space_(Sprite("assets/space.png",0,1,96,96)),
             window(sf::VideoMode(96*3, 96), "DEBUG") {
             Sprite* current_sprite;
             current_sprite = new Sprite("assets/bombs-unpressed.png", 0, 2, 96, 96);
             bombkeys_sprites_.push_back(current_sprite[0]);
             current_sprite = new Sprite("assets/bombs-y.png",0,2,96,96);
             bombkeys_sprites_.push_back(current_sprite[0]);
             current_sprite = new Sprite("assets/bombs-n.png",0,2,96,96);
             bombkeys_sprites_.push_back(current_sprite[0]);
             current_sprite = new Sprite("assets/arrows-unpressed.png", 0, 0, 96, 96);
             arrows_sprites_.push_back(current_sprite[0]);
             current_sprite = new Sprite("assets/arrows-w.png",0,0,96,96);
             arrows_sprites_.push_back(current_sprite[0]);
             current_sprite = new Sprite("assets/arrows-a.png",0,0,96,96);
             arrows_sprites_.push_back(current_sprite[0]);
             current_sprite = new Sprite("assets/arrows-s.png",0,0,96,96);
             arrows_sprites_.push_back(current_sprite[0]);
             current_sprite = new Sprite("assets/arrows-d.png",0,0,96,96);
             arrows_sprites_.push_back(current_sprite[0]);
             window.setPosition(sf::Vector2i(main_window_pos.x + 0.5*main_window_size.x,main_window_pos.y+ main_window_size.y));
             std::cerr << main_window_pos.x << " " << main_window_pos.y << std::endl;
             window.clear(sf::Color(63,63,116));
             window.draw(bombkeys_sprites_[0]);
             window.draw(arrows_sprites_[0]);
           };
  void draw(){
    int arrow_index, bombkeys_index;
    switch(arrows_){
      case ARROWS_ALLUP:
        arrow_index = 0;
        break;
      case W_DOWN:
        arrow_index = 1;
        break;
      case A_DOWN:
        arrow_index = 2;
        break;
      case S_DOWN:
        arrow_index = 3;
        break;
      case D_DOWN:
        arrow_index = 4;
    }
    switch(bombkeys_){
      case BOMBS_ALLUP:
        bombkeys_index = 0;
        break;
      case Y_DOWN:
        bombkeys_index = 1;
        break;
      case N_DOWN:
        bombkeys_index = 2;
    }
    window.draw(arrows_sprites_[arrow_index]);
    window.draw(bombkeys_sprites_.at(bombkeys_index));
    window.draw(space_);
  }
  void in(){
    bool dir_pressed = false;
    bool bomb_pressed = false;
    arrows_ = ARROWS_ALLUP;
    bombkeys_= BOMBS_ALLUP;
    while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dir_pressed && bomb_pressed)){
      window.clear(sf::Color(63,63,116));
      this->draw();
      window.display();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        dir_pressed = true;
        arrows_ = W_DOWN;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        dir_pressed = true;
        arrows_ = A_DOWN;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        dir_pressed = true;
        arrows_ = S_DOWN;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        dir_pressed = true;
        arrows_ = D_DOWN;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
        bomb_pressed = true;
        bombkeys_ = Y_DOWN;
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
        bomb_pressed = true;
        bombkeys_ = N_DOWN;
      }
    }
  }
  char getMove(){
    switch (arrows_){
      case ARROWS_ALLUP:
        return 'h';
      case W_DOWN:
        return 'w';
      case A_DOWN:
        return 'a';
      case S_DOWN:
        return 's';
      case D_DOWN:
        return 'd';
    }
  }
  char getBomb(){
    switch(bombkeys_){
      case BOMBS_ALLUP:
        return 'n';
      case Y_DOWN:
        return 'y';
      case N_DOWN:
        return 'n';
    }
  }
  sf::RenderWindow window;
private:
  std::vector<Sprite> bombkeys_sprites_;
  std::vector<Sprite> arrows_sprites_;
  Sprite space_;
  debug::Arrows arrows_;
  debug::BombKeys bombkeys_;
};
