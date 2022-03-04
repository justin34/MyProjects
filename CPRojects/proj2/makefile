CXX = g++
CXXFLAGS = -Wall

proj2: proj2.cpp Organization.o Person.o FriendFinder.o
	$(CXX) $(CXXFLAGS) proj2.cpp Organization.o Person.o FriendFinder.o -o proj2

FriendFinder.o: FriendFinder.h FriendFinder.cpp Organization.o Person.o
	$(CXX) $(CXXFLAGS) -c FriendFinder.cpp

Organization.o: Organization.h Organization.cpp Person.o
	$(CXX) $(CXXFLAGS) -c Organization.cpp

Person.o: Person.h Person.cpp
	$(CXX) $(CXXFLAGS) -c Person.cpp

run:
	./proj2

clean:
	rm *~
