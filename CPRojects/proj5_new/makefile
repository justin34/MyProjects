CXX = g++
CXXFLAGS = -Wall

proj5: Villain.o Hero.o Game.o proj5.cpp Lqueue.cpp
	$(CXX) $(CXXFLAGS) Hero.o Villain.o Game.o Lqueue.cpp proj5.cpp -o proj5

Game.o: Game.h Game.cpp Lqueue.o Hero.o Villain.o
	$(CXX) $(CXXFLAGS) -c Game.cpp

Lqueue.o: Lqueue.cpp
	$(CXX) $(CXXFLAGS) -c Lqueue.cpp

Villain.o: Villain.h Villain.cpp
	$(CXX) $(CXXFLAGS) -c Villain.cpp

Hero.o: Hero.h Hero.cpp
	 $(CXX) $(CXXFLAGS) -c Hero.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj5 proj5_data.txt

val:
	valgrind --leak-check=full ./proj5 proj5_data.txt

lqueue:
	g++ -Wall lqueue_test.cpp Lqueue.cpp -o lqueue_test

test:
	valgrind ./lqueue_test

submit:
	cp Hero.h Hero.cpp Villain.h Villain.cpp Lqueue.cpp Game.h Game.cpp proj5.cpp ~/cs202proj/proj5
