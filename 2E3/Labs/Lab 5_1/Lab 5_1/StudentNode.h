#pragma once
#include <string>
#include <fstream>

using namespace std;

class StudentNode {
private:
	int ID;
	string lastName;
	string firstName;
	double finalGrade;
	StudentNode* nextS;
	static int numStudents;
	static int deleted;
public:
	StudentNode();
	StudentNode(string, string, int, double);
	//StudentNode(string, double);
	~StudentNode();
	void printStudent();
	int getStudentID();
	string getStudentFN();
	string getStudentLN();
	double getStudentGrade();
	StudentNode* getNext();
	void setNext(StudentNode*);
	int getnumStudents();
	int removedStudent();
	int addedStudent();
	int getDeleted();
	void outputStudent(ofstream&);
};