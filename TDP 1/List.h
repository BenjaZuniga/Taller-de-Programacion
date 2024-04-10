
#include "Node.h"

class List{
	public:
		Node *head;
		int size;

		List();
		~List();
		void push(State *data);
		void add(State *data);
		void remove();
		Node* pop();
		bool isEmpty();
		bool contains(State *data);
		void print();
};
