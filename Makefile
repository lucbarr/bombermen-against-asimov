MAIN = baa
CXX = clang++
CXXFLAGS = -std=c++11
SRC := $(shell find . -name '*.cpp')

all: $(SRC)
				$(CXX) $(CXXFLAGS) $(SRC) -o $(MAIN)
clean:
				rm -f $(MAIN) *.o
