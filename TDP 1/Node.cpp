#include "Node.h"

Node::Node(State *data){
	this->data = data;
	if(data->size == 5){
		this->weight = data->steps*0.6 + data->fails*0.4 + data->missingSteps*1.5;
	}else if(data->size == 4){
		this->weight = data->steps*0.8 + data->fails*0.4 + data->missingSteps*1.2;
	}else if (data->size <= 3){
		this->weight = data->fails*0.4 + data->missingSteps*0.8 + data->steps*1.5;
	}
	
	this->next = nullptr;
}

Node::~Node(){
	delete [] data;
	weight = 0;
	delete [] next;
}