#include "Stack.h"

//Constructor de Stack
Stack::Stack() {
	this->size = 0;
	this->head = nullptr;
}

//Destructor de Stack
Stack::~Stack() {
	StackNode *current= head;
	StackNode *next=current->next;
	while(current!=nullptr){
		StackNode *next=current->next;
		delete current;
		StackNode *current =next;
		}
	delete[] head;
}

//Comprueba si el Stack está vacio
bool Stack::isEmpty() {
	return size == 0;
}

//Agrega un elemento al inicio de la lista
void Stack::add(State *data) {
	StackNode *node = new StackNode(data);
	node->next = head;
	head = node;
	size++;
}

//Comprueba si un estado está en el Stack
bool Stack::contains(State *data) {
	StackNode *current = head;
	while (current != nullptr) {
		if (current->ids[0]==data->id1 && current->ids[1]==data->id2 && current->ids[2]==data->id3) {
			return true;
		}
		current = current->next;
	}
	return false;
}