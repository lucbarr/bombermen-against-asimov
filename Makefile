MAIN = baa.out
CXX = clang++
CXXFLAGS = -std=c++11
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRC := $(shell find . -name '*.cpp')

all: $(SRC)
				$(CXX) $(CXXFLAGS) $(LIBS) $(SRC) -o $(MAIN)
clean:
				rm -f $(MAIN) *.o
