#include <iostream> 
#include <string>
#include "StudentNode.h"

using namespace std;

int StudentNode::numStudents = 0;
int StudentNode::deleted = 0;

StudentNode::StudentNode() {
	firstName = " ";
	finalGrade = 0;
}

//StudentNode::StudentNode(int id, string f_name, double grade) {
//	ID = id;
//	firstName = f_name;
//	finalGrade = grade;
//	nextS = NULL;
//}

StudentNode::StudentNode(string l_name, string f_name, int id, double grade) {
	lastName = l_name;
	firstName = f_name;
	finalGrade = grade;
	ID = id;
	numStudents++;
	nextS = NULL;
}

StudentNode::~StudentNode() {
	deleted++;
	//cout << deleted << " StudentNode(s) deleted!" << endl;
}

void StudentNode::printStudent() {
	cout << "Student Name: " << getStudentLN() << ", " << getStudentFN() << endl;
	cout << "Student ID: " << getStudentID() << endl;
	cout << "Final Grade: " << getStudentGrade() << endl << endl;
}

void StudentNode::outputStudent(ofstream& file) {
	//file << "Student Name: " << getStudentLN() << ", " << getStudentFN() << endl;
	//file << "Student ID: " << getStudentID() << endl;
	//file << "Final Grade: " << getStudentGrade() << endl << endl;
	file << getStudentLN() << " " << getStudentFN();
	file << " " << getStudentID();
	file << " " << getStudentGrade() << endl;
}

int StudentNode::getStudentID() {
	return ID;
}

string StudentNode::getStudentFN() {
	return firstName;
}

string StudentNode::getStudentLN() {
	return lastName;
}

double StudentNode::getStudentGrade() {
	return finalGrade;
}

StudentNode* StudentNode::getNext() {
	return nextS;
}

void StudentNode::setNext(StudentNode* _next) {
	nextS = _next;
}

int StudentNode::getnumStudents() {
	return numStudents;
}

int StudentNode::removedStudent() {
	return numStudents--;
}

int StudentNode::addedStudent() {
	return numStudents++;
}

int StudentNode::getDeleted() {
	return deleted;
}