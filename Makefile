MAIN = baa
CXX = g++
CXXFLAGS = -std=c++11
SRC := $(shell find . -name '*.cpp')

all: $(SRC)
				$(CXX) $(CXXFLAGS) -c $(SRC)
				$(CXX) $(CXXFLAGS) *.o -o $(MAIN)
clean:
				rm -f $(MAIN) *.o
