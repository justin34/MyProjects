CXX = g++
CXXFLAGS = -Wall -g

proj4: mytest.cpp dnadb.cpp
	$(CXX) $(CXXFLAGS) mytest.cpp dnadb.cpp -o proj4

run:
	./proj4

val:
	valgrind --leak-check=full ./proj4

##Use this to clean out your directory
clean:
	rm *.o

##Use this when you want to debug your whole project
debug1:
	gdb gdbarg1 --args ./proj4
