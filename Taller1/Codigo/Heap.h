#include <iostream>
#include "State.h"

class Heap {
public:
    State **arr;
    int capacity;
    int size; // indice del ultimo no ocupado o cantidad de elementos
    Heap(int capacity);
    ~Heap();
    void push(State *data);
    State *pop();
	bool isEmpty();
	
};