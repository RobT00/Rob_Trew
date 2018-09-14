//List.h
//Defines a simple linked list class called List
#include "Node.h"

class List {
private:
	Node* headP;	//a pointer to the first node in list
	Node* tailP;	//a point to the last node in list
	int length;		//the length of the list
public:
	List();			//Constructor to create an empty list
	~List();		//Destructor that deletes all nodes in the list
	void addNode(int newData);	//Add a node to the end of the list
	bool removeNode(int _data);	//Remove a node that contains the integer passed in
	void print();	//Print out all the data values in the list
};
