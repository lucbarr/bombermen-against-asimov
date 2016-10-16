#pragma once

class Intel {

public:
  virtual void step(Map&) = 0;
  virtual void setBomb(Map&) = 0;
};

