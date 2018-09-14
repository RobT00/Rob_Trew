//Node.h
//Defines the node class
#pragma once
#include <iostream>
using namespace std;

class Node {
private:
	int data;		//a number
	Node* nextP;	//a pointer to the next node
public:
	Node(int newData);	//set the data to the integer passed in
	int getData();		//return the value of data
	Node* getNext();	//return the value of the next pointer
	void setNext(Node* _next);	//set the value of the next pointer
};


