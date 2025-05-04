CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

all: Main test

Main: Main.o SquareMat.o
	$(CXX) $(CXXFLAGS) -o Main Main.o SquareMat.o

test: Test.o SquareMat.o
	$(CXX) $(CXXFLAGS) -o test Test.o SquareMat.o

Main.o: Main.cpp SquareMat.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

Test.o: Test.cpp SquareMat.h
	$(CXX) $(CXXFLAGS) -c Test.cpp

SquareMat.o: SquareMat.cpp SquareMat.h
	$(CXX) $(CXXFLAGS) -c SquareMat.cpp

valgrind: Main
	valgrind --leak-check=full --show-leak-kinds=all ./Main

clean:
	rm -f *.o Main test 
