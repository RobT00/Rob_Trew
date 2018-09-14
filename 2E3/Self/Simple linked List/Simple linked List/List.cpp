#include "List.h"

List::List(){
	headP = NULL; 
	tailP = NULL; 
	length = 0; 
}

List::~List(){
	//Destructor -- free up all used nodes
	Node* curr=headP; //start at head of list
	Node* next;

	while (curr != NULL) { //iterate until end
		next = curr->getNext(); //remember what next one is
		delete curr; //delete the current one
		curr = next; //move to the next one
	}
}

void List::print() {
	Node* currNode;
	currNode = headP;
	while (currNode != NULL) {
		cout << currNode->getData() << " ";
		currNode = currNode->getNext();
	}
	cout << endl;
}

void List::addNode(int newData) {

	//create the new node
	Node* newNode = new Node(newData);
	
	//add it to the tail of the list
	if (tailP == NULL)
		//list was empty
		headP = tailP = newNode;
	else {
		//list not empty
		tailP->setNext(newNode);
		tailP = newNode;
	}
	length++;
}

bool List::removeNode(int _data) {
	//Scan the list looking for 1st occurrence of data
	Node* curr = headP;
	Node* prev = headP;

	while (curr != 0) {
		if (curr->getData() == _data) {
			//found it so remove it
			if (curr == headP) {
				//this is the first element
				headP = curr->getNext();
			}//4
			else {
				//not the first element
				prev->setNext(curr->getNext());
				if (curr == tailP) {
					//this is the last element
					tailP = prev;
				}
			}
			cout << "DEL" << endl;
			delete curr;
			length--;
			return true;
		}
		//Move to the next one, using prev to remember previous node
		prev = curr;
		curr=curr->getNext();
	}
	//If we get to here then none found
	return false;
}