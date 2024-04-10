all: State.o Stack.o Puzzle.o main 

State.o: State.cpp State.h
	g++ -g -c State.cpp

Stack.o: Stack.cpp Stack.h
	g++ -g -c Stack.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -g -c Puzzle.cpp

main: Puzzle.o State.o Stack.o main.cpp
	g++ -g State.o Stack.o Puzzle.o main.cpp -o main

