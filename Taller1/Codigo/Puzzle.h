#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Heap.h"
#include "Stack.h"
using namespace std;


class Puzzle {
	public:
	 
    	State *act_stat;  // la matriz que representa el puzzle original
		Heap *open;
    	Stack *closed;

    	Puzzle(string  filename); // cargar desde filename el tablero inicial
    	~Puzzle();
		void solve(); // opera el algoritmo A*
};