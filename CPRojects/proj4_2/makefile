CXX = g++
CXXFLAGS = -Wall

proj4: Track.o proj4.cpp Mario.o Wario.o Toad.o Character.o Entity.o Banana.o Shell.o Obstacle.o Game.o
	$(CXX) $(CXXFLAGS) proj4.cpp Track.o Mario.o Wario.o Toad.o Character.o Entity.o Obstacle.o Banana.o Game.o Shell.o -o proj4

Game.o:  Track.o Mario.o Wario.o Toad.o Character.o Entity.o Banana.o Shell.o Obstacle.o Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Shell.o: Obstacle.o Shell.h Shell.cpp
	$(CXX) $(CXXFLAGS) -c Shell.cpp

Banana.o: Banana.h Banana.cpp Obstacle.o
	$(CXX) $(CXXFLAGS) -c Banana.cpp

Obstacle.o: Obstacle.cpp Obstacle.h
	$(CXX) $(CXXFLAGS) -c Obstacle.cpp

Wario.o: Wario.h Wario.cpp Character.o Entity.o
	$(CXX) $(CXXFLAGS) -c Wario.cpp

Toad.o: Toad.h Toad.cpp Character.o Entity.o
	$(CXX) $(CXXFLAGS) -c Toad.cpp

Mario.o: Mario.h Mario.cpp Character.o Entity.o
	$(CXX) $(CXXFLAGS) -c Mario.cpp

Character.o: Character.h Character.cpp Entity.o
	$(CXX) $(CXXFLAGS) -c Character.cpp

Entity.o: Entity.h Entity.cpp
	$(CXX) $(CXXFLAGS) -c Entity.cpp

Track.o: Track.cpp Track.h
	$(CXX) $(CXXFLAGS) -c Track.cpp

run:
	./proj4

val:
	valgrind ./proj4

clean:
	rm *~
	rm *.o

submit:
	cp Track.h Track.cpp Entity.h Entity.cpp Character.h Character.cpp Mario.h Mario.cpp Wario.h Wario.cpp Toad.h Toad.cpp Obstacle.h Obstacle.cpp Banana.h Banana.cpp Shell.h Shell.cpp Game.h Game.cpp proj4.cpp ~/cs202proj/proj4

check:
	ls ~/cs202proj/proj4
