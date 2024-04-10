#include "State.h"

class Node{
	public:
		State *data;
		float weight;
		Node *next;

		Node(State *data);
		~Node();
};