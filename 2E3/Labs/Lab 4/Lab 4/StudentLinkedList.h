#pragma once
#include <string>
//#include "Student.h"
#include "StudentNode.h"

using namespace std;

class StudentLinkedList {
private:
	StudentNode* headP;
	StudentNode* tailP;
//	static int length;
public:
	StudentLinkedList();
	~StudentLinkedList();
	void printAllStudents(); //loop through from head to tail, printing the data
	void printOneStudent(StudentNode* );
	StudentNode* findByName(string); //loop through until the name is found,	then return that node
	StudentNode* findByID(int); //ditto for ID
	void addStudent(string, double ); //add a new node
	bool removeStudent(string); //find the student with the given name and delete him/her
	bool removeStudent(int); //find the student with the given ID and delete him/her
	bool removeStudent(StudentNode*); //delete the student pointed to
	bool insertStudentAfter(StudentNode* , string ); //insert the student node after the student named
	bool insertStudentAfterCheckH(StudentNode*);
	bool insertStudentAfterCheckT(StudentNode*);
	int getListLength();
	int checkListLength();
};