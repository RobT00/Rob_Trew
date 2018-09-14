//Using Linked List.cpp
//Using the List class to add, print and remove nodes
#include "List.h"

void main() {
	List l1; //Declare an empty list

	int num=0; //Local variable

	while (num != 99) { //Loop until user types 99
		cout << "Enter number: ";
		cin >> num;
		if(num!=99)
			l1.addNode(num); //Add number to list
	}
	l1.print(); //Print out the list

	num = 0;	//reset local variable
	while (num != 99) { //Loop until user types 99
		cout << endl << "Enter a value to delete from list: ";
		cin >> num;
		if (num != 99)
			if (!l1.removeNode(num)) { //remove the node and check if it was successful
				cout << "No such node in list!" << endl;
			}
	}
	
	l1.print();
}