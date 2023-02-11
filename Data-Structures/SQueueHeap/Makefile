CXX = g++
CXXFLAGS = -Wall -g

proj3: mytest.cpp squeue.cpp
	$(CXX) $(CXXFLAGS) mytest.cpp squeue.cpp -o proj3

run:
	./proj3

val:
	valgrind --leak-check=full ./proj3

##Use this to clean out your directory
clean:
	rm *.o

##Use this when you want to debug your whole project
debug1:
	gdb gdbarg1 --args ./proj3
