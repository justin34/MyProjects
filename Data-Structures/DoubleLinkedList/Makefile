CXX = g++
CXXFLAGS = -Wall -g

proj1: mytest.cpp elevator.cpp
	$(CXX) $(CXXFLAGS) mytest.cpp elevator.cpp -o proj1

run:
	./proj1

val:
	valgrind ./proj1

##Use this to clean out your directory
clean:
	rm *.o

##Use this when you want to debug your whole project
debug1:
	gdb gdbarg1 --args ./proj1
