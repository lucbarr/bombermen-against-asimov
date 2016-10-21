# Artificial Intelligences

In this directory, you can code your own AI to play against other AI in the field of play. It must be an abstraction
from Intel class in source code. This means it has to have a sendCommand() method defined, which name is self explanatory.
This method must return a Command cluster, which contains : 

 - a MOVE enum, which can be NORTH, SOUTH, EAST, WEST and HALT, named move corresponding to what movement you want to perform with your AI.
 - a bool set_bomb, corresponding on wether you want to place a bomb or not at the corresponding time.

You can design your AI however you want, you can add many other methods to calculate decisions, you can define
the calculations inside the main methods, you can just stare at this code and try to comprehend it, you can swear me
for coding poorly... As long as your sendCommand() method returns a Command type. Let your knowledge and creativity be your will!
