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

StudentNode::StudentNode(int id, string f_name, double grade) {
	ID = id;
	firstName = f_name;
	finalGrade = grade;
	nextS = NULL;
}

StudentNode::StudentNode(string f_name, double grade) {
	firstName = f_name;
	finalGrade = grade;
	ID = numStudents;
	numStudents++;
	nextS = NULL;
}

StudentNode::~StudentNode() {
	deleted++;
	cout << deleted << " StudentNode(s) deleted!" << endl;
}

void StudentNode::printStudent() {
	cout << "Student Name: " << getStudentFN() << endl;
	cout << "Student ID: " << getStudentID() << endl;
	cout << "Final Grade: " << getStudentGrade() << endl << endl;
}

int StudentNode::getStudentID() {
	return ID;
}

string StudentNode::getStudentFN() {
	return firstName;
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