#pragma once
#include <string>
#include "StudentNode.h"
#include <fstream>

using namespace std;

class StudentLinkedList {
private:
	StudentNode* headP;
	StudentNode* tailP;
	int numberOfComparisons;
public:
	StudentLinkedList();
	~StudentLinkedList();
	void printAllStudents(); //loop through from head to tail, printing the data
	void printOneStudent(StudentNode*);
	StudentNode* findByFName(string); //loop through until the name is found, then return that node
	StudentNode* findByLName(string);
	StudentNode* findByID(int); //ditto for ID
	void addStudent(string, string, int, double); //add a new node
	//StudentNode* addStudent(StudentNode*, string, string, int, double);
	bool removeStudent(string); //find the student with the given name and delete him/her
	bool removeStudent(int); //find the student with the given ID and delete him/her
	bool removeStudent(StudentNode*); //delete the student pointed to
	bool insertStudentAfter(StudentNode*, StudentNode*); //insert the student node after the StudentNode passed in (2nd one)
	void insertStudentAtHead(StudentNode*, StudentNode*);
	//bool insertStudentAfterSpecial(StudentNode*, string);
	bool insertStudentAfterCheckH(StudentNode*);
	bool insertStudentAfterCheckT(StudentNode*);
	bool insertStudentBefore(StudentNode*, StudentNode*);
	bool insertStudentAfterHead(StudentNode*);
	int getListLength();
	int checkListLength();
	StudentNode* findStudent(string, string); //return a pointer to Student with matching lastname and firstname, NULL if not found
	void outputLinkedList(ofstream&);
};