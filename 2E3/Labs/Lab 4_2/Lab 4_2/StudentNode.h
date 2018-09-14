#pragma once
#include <string>

using namespace std;

class StudentNode {
private:
	int ID;
	string firstName;
	double finalGrade;
	StudentNode* nextS;
	static int numStudents;
	static int deleted;
public:
	StudentNode();
	StudentNode(int, string, double);
	StudentNode(string, double);
	~StudentNode();
	void printStudent();
	int getStudentID();
	string getStudentFN();
	double getStudentGrade();
	StudentNode* getNext();
	void setNext(StudentNode*);
	int getnumStudents();
	int removedStudent();
	int addedStudent();
	int getDeleted();
};