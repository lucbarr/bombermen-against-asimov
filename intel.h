#pragma once

// Definition of Command data structure.
enum MOVE{
  NORTH,
  SOUTH,
  EAST,
  WEST,
  HALT
};

struct Command{
  MOVE move;
  bool set_bomb;
};

// Intel is a base class for an AI to perform in game.
class Intel {

public:
  // Alleged to send commands so Game can perform them.
  // Must be redefined for each derived from Intel class.
  virtual Command sendCommand() = 0;
  void setId(int id) { id_ = id; }
private:
  int id_;
};

