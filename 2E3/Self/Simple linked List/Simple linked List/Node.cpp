//Node.cpp
//Implements constructor, getter and setter methods

#include "Node.h"

Node::Node(int newData){
	data = newData; //initialise the data of the new node
	nextP = NULL;	//doesn't point to anything yet
}

int Node::getData() { //getter method for the data
	return data;
}

Node* Node::getNext() { //getter method for pointer to next node
	return nextP;
}

void Node::setNext(Node* _next) { //setter method for pointer to next node
	nextP = _next;
}