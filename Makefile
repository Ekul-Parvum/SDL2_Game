CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

all: test

test: main.o
	$(CXX) main.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o test.exe

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o *.gch main