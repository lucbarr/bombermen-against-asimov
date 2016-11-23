# Artificial Intelligences

In this directory, you can code your own AI to play against other AI in the field of play. It must be an abstraction
from Intel class in source code. This means it has to have a sendCommand() method defined, which name is self explanatory.
This method must return a Command cluster, which contains : 

 - a MOVE enum, which can be NORTH, SOUTH, EAST, WEST and HALT, named move corresponding to what movement you want to perform with your AI.
 - a bool set_bomb, corresponding on wether you want to place a bomb or not at the corresponding time.

Which are sent based on the information contained in a Gamestate cluster, which has:
 - a vector of Vec2d (contains an integer x and a integer y) of bomb positions, named 'bombs'. For example, bombs[0].x is the x position of the first bomb in the vector (if has none, there will be an error);
 - a vector of Vec2d of agents positions, named 'agents'. Same thing as bomb positions;
 - a Blockmap of blocks named 'blocks'. It is basically a matrix of BLOCK_TYPE, where blocks[0][1]
 is a BLOCK_TYPE(FREE, BREAKABLE or UNBREAKABLE) at the position x = 0 and y = 1;
 - a Vec2d self, which is the position of the given intel's agent. self.y is the y coordinate
 of the intel's agent, for example. And
 - two integers, map_width and map_height, which corresponds respectively to the numbers of columns and rows of the map.
 
The axis are disposed as x rises column-wise and y rises row-wise (downwards is positive y and leftwards is positive x):

```
(0,0)------> x +
  |
  |
  |
  V
  +y
```
After designing your AI, head to main.cpp file, add the lines:

```
#include "AIs/myai.h"

//code...

MyAI myai;
game.linkIntel(&myai);
```
Just as is done with DumbBot. You can simply replace names DumbBot by your AI class name. In file DumbBot you can find a template of how should your AI class be. Soon you will not need all this effort to import your AI, there are plans on turning this process more natural and easy to do.

Rebuild the project and you're ready to go!

You can design your AI however you want, you can add many other methods to calculate decisions, you can define
the calculations inside the main methods, you can just stare at this code and try to comprehend it, you can swear me
for coding poorly... As long as your sendCommand() method returns a Command type. Let your knowledge and creativity be your will!

