CXX = g++
CXXFLAGS = -Wall -g

proj2: mytest.cpp fleet.cpp
	$(CXX) $(CXXFLAGS) mytest.cpp fleet.cpp -o proj2

run:
	./proj2

val:
	valgrind --leak-check=full ./proj2

##Use this to clean out your directory
clean:
	rm *.o

##Use this when you want to debug your whole project
debug1:
	gdb gdbarg1 --args ./proj2
