//#include "Student.h"
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//int Student::numStudents = 0;
//Student::Student() {
//	cout << "Please entert the Student's name: ";
//	cin >> firstName;
//	cout << "Please enter " << firstName << "'s final grade: ";
//	cin >> finalGrade;
//	ID = numStudents;
//	numStudents++;
//}
//
//void Student::Buffer_Overload() {
//	finalGrade = 0;
//	numStudents--;
//}
//
//void student::readmarks() {
//	cout << "student: " << s_name << ", " << f_name << endl;
//	cout << "student id: " << studentid << endl;
//	for (int i = 0; i < size; i++) {
//		cout << "please enter the lab mark for lab " << i + 1 << ": ";
//		cin >> labs[i];
//		while (labs[i] < 0 || labs[i] > 100) {
//			cout << "please enter the lab mark for lab " << i + 1 << ": " << endl;
//			cin >> labs[i];
//		}
//	}
//	cout << "please enter the exam mark: ";
//	cin >> exam;
//	while (exam < 0 || exam > 100) {
//		cout << "please enter the exam mark: ";
//		cin >> exam;
//	}
//}
//
//void Student::printFinalGrade() {
//	cout << "Final grade for student: " << firstName << endl;
//	cout << "Student ID: " << ID << endl;
//	cout << finalGrade << endl;
//}
//
//string Student::get_StudentName() const {
//	return firstName;
//}
//
//int Student::get_StudentID() const {
//	return ID;
//}