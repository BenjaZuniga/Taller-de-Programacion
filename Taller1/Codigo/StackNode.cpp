#include "StackNode.h"

//Constructor de un StackNode
StackNode::StackNode(State *data) {
	this->ids = new long[3]; //Guarda los ids de un estado
	this->ids[0] = data->id1;
	this->ids[1] = data->id2;
	this->ids[2] = data->id3;
	this->next = nullptr;
}

//Destructor de un StackNode
StackNode::~StackNode() {
	delete [] ids;
}