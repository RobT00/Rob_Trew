#pragma once
#include <string>
#include "StudentNode.h"
#include <fstream>

using namespace std;

class StudentLinkedList {
private:
	StudentNode* root;
	StudentNode* findStudent(StudentNode*, string, string);
	int numberOfComparisons;
public:
	StudentLinkedList();
	//~StudentLinkedList();
	//void printAllStudents(); //loop through from head to tail, printing the data
	void printOneStudent(StudentNode*);
	void addStudent(string, string, int, double); //add a new node
	//int getListLength();
	//int checkListLength();
	StudentNode* findStudent(string, string); //return a pointer to Student with matching lastname and firstname, NULL if not found
	//void outputLinkedList(ofstream&);
};