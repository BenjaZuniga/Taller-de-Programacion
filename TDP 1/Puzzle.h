#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "List.h"
using namespace std;


class Puzzle {
	public:
	 
    	State *act_stat;  // la matriz que representa el puzzle original
    	List *open;
    	List *closed;

    	Puzzle(string  filename); // cargar desde filename el tablero inicial
    	~Puzzle();
    	void solve(); // opera el algoritmo A*
};