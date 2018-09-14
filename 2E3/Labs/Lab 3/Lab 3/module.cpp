#include <iostream>
#include <string>
#include "Student.h"
#include "Module.h"

using namespace std;

void Module::readallMarks() {
	for (int i = 0; i < SIZE; i++)
		students[i].readMarks();
}

void Module::printallGrades() {
	for (int i = 0; i < SIZE; i++)
		students[i].printFinalGrade();
}

int Module::findByName(string last_name) {
	for (int i = 0; i < SIZE; i++) {
		if (last_name == students[i].get_StudentLN()) {
			return i;
		}
	}
	return -5;
}

string Module::findByID(int studentID) {
	for (int i = 0; i < SIZE; i++) {
		if (studentID == students[i].get_StudentID())
			return (students[i].get_StudentLN());
	}
	return "NO";
}