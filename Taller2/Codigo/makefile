all: Clique.o testClique main

Clique.o: Clique.cpp Clique.h
	g++ -c Clique.cpp

testClique: testClique.cpp Clique.o
	g++ testClique.cpp Clique.o -o testClique

main: main.cpp Clique.o
	g++ main.cpp Clique.o -o main

clean:
	rm -f *.o testClique main