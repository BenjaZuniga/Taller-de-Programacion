#include <iostream>
#include "State.h"

class StackNode {
public:
	long *ids;
	StackNode *next;

	StackNode(State *data);
	~StackNode();
};