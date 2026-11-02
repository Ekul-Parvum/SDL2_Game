CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: all clean

all: test

# -- -- -- --[ Linking everything together ]-- -- -- --
test: main.o window.o gameobject.o
	$(CXX) ./bin/main.o ./bin/window.o ./bin/gameobject.o $(LDLIBS) -o ./test.exe
# -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

# -/- -/- -/- -/-[  Making Object Files  ]-\- -\- -\- -\-
main.o: ./src/main.cpp ./src/Global.h ./src/GameObject.h ./src/Window.h
	$(CXX) $(CXXFLAGS) -c ./src/main.cpp -o ./bin/main.o

window.o: ./src/Window.cpp ./src/Window.h ./src/Global.h
	$(CXX) $(CXXFLAGS) -c ./src/Window.cpp -o ./bin/window.o

gameobject.o: ./src/GameObject.cpp ./src/GameObject.h
	$(CXX) $(CXXFLAGS) -c ./src/GameObject.cpp -o ./bin/gameobject.o
# -\- -\- -\- -\- -\- -\- -\- -/- -/- -/- -/- -/- -/- -/-

clean:
	rm -f *.o *.gch test.exe ./bin/*.o ./bin/*.gch ./bin/test.exe