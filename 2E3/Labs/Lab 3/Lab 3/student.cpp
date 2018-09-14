#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

int Student::numStudents = 0;
Student::Student() {
	for (int i = 0; i < SIZE; i++)
		labs[i] = 0;
	exam = finalGrade = 0;
	studentID = numStudents;
	cout << "Please input the last and first name of the student: ";
	cin >> s_name >> f_name;
	numStudents++;
}

void Student::Buffer_Overload() {
	for (int i = 0; i < SIZE; i++)
		labs[i] = 0;
	exam = finalGrade = 0;
	numStudents--;
}

void Student::readMarks() {
	cout << "Student: " << s_name << ", " << f_name << endl;
	cout << "Student ID: " << studentID << endl;
	for (int i = 0; i < SIZE; i++) {
		cout << "Please enter the lab mark for lab " << i + 1 << ": ";
		cin >> labs[i];
		while (labs[i] < 0 || labs[i] > 100) {
			cout << "Please enter the lab mark for lab " << i + 1 << ": " << endl;
			cin >> labs[i];
		}
	}
	cout << "Please enter the exam mark: ";
	cin >> exam;
	while (exam < 0 || exam > 100) {
		cout << "Please enter the exam mark: ";
		cin >> exam;
	}
}

void Student::printFinalGrade() {
	cout << "Final Grade for student: " << s_name << ", " << f_name << endl;
	cout << "Student ID: " << studentID << endl;
	double lab_mark = 0;
	for (int i = 0; i < SIZE; i++)
		lab_mark = lab_mark + labs[i];
	lab_mark = lab_mark / SIZE;
	lab_mark = lab_mark * 0.4;
	exam = exam * 0.6;
	finalGrade = lab_mark + exam;
	cout << finalGrade << endl;
}

string Student::get_StudentLN() const {
	return s_name;
}

int Student::get_StudentID() const {
	return studentID;
}