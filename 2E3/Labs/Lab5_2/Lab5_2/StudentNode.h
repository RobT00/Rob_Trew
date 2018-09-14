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
	StudentNode* left;
	StudentNode* right;
	static int numStudents;
public:
	//StudentNode();
	StudentNode(string, string, int, double);
	//~StudentNode();
	void printStudent();
	int getStudentID();
	string getStudentFN();
	string getStudentLN();
	double getStudentGrade();
	void setLeft(StudentNode* n) { left = n; }
	void setRight(StudentNode* n) { right = n; }
	StudentNode* getLeft() { return left; }
	StudentNode* getRight() { return right; }
	void setID(int x) { ID = x; }
	void setlastName(string x) { lastName = x; }
	void setfirstName(string x) { firstName = x; }
	void setfinalGrade(double x) { finalGrade = x; }
	int getnumStudents();
	int addedStudent();
	//void outputStudent(ofstream&);
};