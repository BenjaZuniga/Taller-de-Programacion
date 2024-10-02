#include <iostream>
#include "StackNode.h"

class Stack {
public:
    StackNode *head;
    int size; // indice del ultimo no ocupado o cantidad de elementos

    Stack();
    ~Stack();
    void add(State *data);
	bool contains(State *data);
	bool isEmpty();
	
};