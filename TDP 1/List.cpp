#include <iostream>
#include "List.h"

List::List(){
	head = nullptr;
	size = 0;

}

List::~List(){
	delete [] head;
}

void List::push(State *data){
	Node *node = new Node(data);
	if(head == nullptr){
		head = node;	
	}else{
		/*if(data->size == 5 && node->weight > 500){
			return;
		}
		if(data->size == 4 && node->weight > 200){
			return;
			}*/
		if(head->weight > node->weight){
			node->next = head;
			head = node;
		}
		else{
			Node *temp = head;
			while(temp->next != nullptr && temp->next->weight < node->weight){
				temp = temp->next;
			}
			node->next = temp->next;
			temp->next = node;
		}
	}
	size++;
}

void List::add(State *data){
	Node *node = new Node(data);
	if(head == nullptr){
		head = node;	
	}else{
		node->next = head;
		this->head = node;
	}
	size++;
}

Node* List::pop(){
	if(head == nullptr){
		return nullptr;
	}
	Node *temp = head;
	head = head->next;
	size--;
	return temp;
}

void List::remove(){
	if(head == nullptr){
		return;
	}
	Node *temp = head;
	head = head->next;
	delete temp;
}

bool List::isEmpty(){
	if(head == nullptr){
		return true;
	}
	return false;
}

bool List::contains(State *data){
	Node *temp = head;
	while(temp != nullptr){
		if(temp->data->equals(data)){
			return true;
		}
		temp = temp->next;
		}
	return false;
}


void List::print(){
	Node *temp = head;
	while(temp != nullptr){
		temp->data->print_act();
		temp = temp->next;
	}
}

