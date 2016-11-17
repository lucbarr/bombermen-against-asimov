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
  Sprite(const std::string& sprite, int j, int i){
    if (!texture_.loadFromFile(sprite, sf::IntRect(0,0,32,32))){
      std::cerr << "[GUI ERROR]: couldn't load sprite file:" << sprite << std::endl;
    } else {
      this->setTexture(texture_);
      this->setPosition(sf::Vector2f(i*32,j*32));
    }
  }
  void update(int j, int i){
    this->setPosition(sf::Vector2f(i*32,j*32));
  }
private:
  sf::Texture texture_;
};

