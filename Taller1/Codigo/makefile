all: State.o Heap.o StackNode.o Stack.o Puzzle.o testState testHeap testStackNode testStack testPuzzle main

State.o: State.cpp State.h
	g++ -g -c State.cpp

Heap.o: Heap.cpp Heap.h
	g++ -g -c Heap.cpp

StackNode.o: StackNode.cpp StackNode.h
	g++ -g -c StackNode.cpp
	
Stack.o: Stack.cpp Stack.h
	g++ -g -c Stack.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -g -c Puzzle.cpp

testState: testState.cpp State.o
	g++ -g State.o testState.cpp -o testState

testHeap: testHeap.cpp Heap.o  State.o 
	g++ -g State.o Heap.o testHeap.cpp -o testHeap

testStackNode: testStackNode.cpp StackNode.o State.o 
	g++ -g State.o StackNode.o testStackNode.cpp -o testStackNode

testStack: State.o StackNode.o Stack.o testStack.cpp
	g++ -g State.o StackNode.o Stack.o testStack.cpp -o testStack

testPuzzle: Puzzle.o State.o Heap.o StackNode.o Stack.o testPuzzle.cpp
	g++ -g State.o Heap.o StackNode.o Stack.o Puzzle.o testPuzzle.cpp -o testPuzzle

main: Puzzle.o State.o Heap.o StackNode.o Stack.o main.cpp
	g++ -g State.o Heap.o StackNode.o Stack.o Puzzle.o main.cpp -o main

clean:
	rm -f *.o testState testHeap testStackNode testStack testPuzzle main

