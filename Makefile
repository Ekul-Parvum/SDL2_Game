CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: all clean

all: test

test: main.o window.o gameobject.o texture.o
	$(CXX) main.o window.o gameobject.o texture.o $(LDLIBS) -o test.exe

main.o: main.cpp Constants.h GameObject.h Window.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

window.o: Window.cpp Window.h Constants.h
	$(CXX) $(CXXFLAGS) -c Window.cpp -o window.o

gameobject.o: GameObject.cpp GameObject.h texture.o
	$(CXX) $(CXXFLAGS) -c GameObject.cpp -o gameobject.o

texture.o: Texture.cpp Texture.h
	$(CXX) $(CXXFLAGS) -c Texture.cpp -o texture.o

clean:
	rm -f *.o *.gch test.exe