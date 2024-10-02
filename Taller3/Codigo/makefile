

all: Simplex.o testSimplex main

Simplex.o: Simplex.cpp Simplex.h
	g++ -c Simplex.cpp

testSimplex: testSimplex.cpp Simplex.o
	g++ testSimplex.cpp Simplex.o -o testSimplex

main: main.cpp Simplex.o
	g++ main.cpp Simplex.o -o main
clean:
	rm -f *.o testSimplex main 
