CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: all clean

all: test

# -- -- -- --[ Linking everything together ]-- -- -- --
test: main.o window.o gameobject.o physicsobject.o
	$(CXX) ./obj/main.o ./obj/window.o ./obj/gameobject.o ./obj/physicsobject.o $(LDLIBS) -o ./test.exe
# -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

# -/- -/- -/- -/-[  Making Object Files  ]-\- -\- -\- -\-
main.o: ./src/main.cpp ./src/Global.h ./src/GameObject.h ./src/Window.h
	$(CXX) $(CXXFLAGS) -c ./src/main.cpp -o ./obj/main.o

window.o: ./src/Window.cpp ./src/Window.h ./src/Global.h
	$(CXX) $(CXXFLAGS) -c ./src/Window.cpp -o ./obj/window.o

gameobject.o: ./src/GameObject.cpp ./src/GameObject.h
	$(CXX) $(CXXFLAGS) -c ./src/GameObject.cpp -o ./obj/gameobject.o

physicsobject.o: ./src/PhysicsObject.cpp ./src/PhysicsObject.h
	$(CXX) $(CXXFLAGS) -c ./src/PhysicsObject.cpp -o ./obj/physicsobject.o
# -\- -\- -\- -\- -\- -\- -\- -/- -/- -/- -/- -/- -/- -/-

clean:
	rm -f *.o *.gch test.exe ./obj/*.o ./obj/*.gch ./obj/test.exe