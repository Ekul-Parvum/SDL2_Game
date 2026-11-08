CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

.PHONY: all clean

all: test

# -- -- -- --[ Linking everything together ]-- -- -- --
test: main.o window.o texture.o physicsobject.o gameobject.o physicsengine.o
	$(CXX) ./obj/main.o ./obj/window.o ./obj/texture.o ./obj/physicsobject.o ./obj/gameobject.o ./obj/physicsengine.o $(LDLIBS) -o ./test.exe
# -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

# -/- -/- -/- -/-[  Making Object Files  ]-\- -\- -\- -\-
main.o: ./src/main.cpp ./src/Global.h ./src/Window.h ./src/GameObject.h ./src/PhysicsEngine.h
	$(CXX) $(CXXFLAGS) -c ./src/main.cpp -o ./obj/main.o

window.o: ./src/Window.cpp ./src/Window.h ./src/Global.h
	$(CXX) $(CXXFLAGS) -c ./src/Window.cpp -o ./obj/window.o

texture.o: ./src/Texture.cpp ./src/Texture.h
	$(CXX) $(CXXFLAGS) -c ./src/texture.cpp -o ./obj/texture.o

physicsobject.o: ./src/PhysicsObject.cpp ./src/PhysicsObject.h
	$(CXX) $(CXXFLAGS) -c ./src/PhysicsObject.cpp -o ./obj/physicsobject.o

physicsengine.o: ./src/PhysicsEngine.cpp ./src/PhysicsEngine.h
	$(CXX) $(CXXFLAGS) -c ./src/PhysicsEngine.cpp -o ./obj/physicsengine.o

gameobject.o: ./src/GameObject.cpp ./src/GameObject.h ./src/PhysicsObject.h ./src/Texture.h ./src/PhysicsEngine.h
	$(CXX) $(CXXFLAGS) -c ./src/GameObject.cpp -o ./obj/gameobject.o
# -\- -\- -\- -\- -\- -\- -\- -/- -/- -/- -/- -/- -/- -/-

clean:
	rm -f *.o *.gch test.exe ./obj/*.o ./obj/*.gch ./obj/test.exe