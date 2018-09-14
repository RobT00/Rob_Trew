#include <iostream>
#include <string>
//#include <iomanip>
//#include "Student.h"
#include "StudentNode.h"
#include "StudentLinkedList.h"

using namespace std;

int main() {
//	StudentNode s0;
	StudentLinkedList sll0;
	StudentNode* select;
	string name;
	double grade;
	int id;

	//cout << "Please enter the id of the student: ";
	//cin >> id;
	//cout << "Please enter the student's name: ";
	//cin >> name;
	//cout << "Please entert the student's grade: ";
	//cin >> grade;
//	StudentNode s0(45, "John", 100);
//	cout << endl;
	StudentNode* s0 = new StudentNode(100, "John", 45);
	cout << "***** Printing StudentNode* s0 *****" << endl;
	s0->printStudent();

	cout << string(50, '*') << endl;
	cout << "\n***** Genertaing StudentLinkedList sll0 *****" << endl;
	for (int i = 0; i < 5; i++) {
		cout << "Enter student's name: ";
		cin >> name;
		cout << "Enter student's grade: ";
		while (!(cin >> grade)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter student's grade: ";
		}
		while ((grade < 0) || (grade > 100)) {
			cout << "Enter student's grade: ";
			cin >> grade;
		}	
		sll0.addStudent(name, grade);
		cout << endl;
	}
	cout << endl;
	sll0.printAllStudents();
	cout << "***** Initial List Length: " << sll0.getListLength() << " *****" << endl;
	cout << string(60, '-') << endl << endl;
	
	cout << "Please enter the name of the student you wish to remove: ";
	cin >> name;
	select = sll0.findByName(name);
	while (select == NULL) {
		cout << "Student Not Found!" << endl;
		cout << "Please enter the name of the student you wish to remove: ";
		cin >> name;
		select = sll0.findByName(name);
	}
	cout << "\nThe student to be removed is:" << endl;
	sll0.printOneStudent(select);
	if (!sll0.removeStudent(name))
		cout << "FAIL" << endl;

	cout << endl;
	sll0.printAllStudents();
	cout << "***** Current List Length: " << sll0.getListLength() << " *****" << endl;
	cout << string(60, '-') << endl << endl;

	cout << "Please enter the Student ID of the student you wish to remove: ";
	while (!(cin >> id)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter the Student ID of the student you wish to remove: ";
	}
	select = sll0.findByID(id);
	while (select == NULL) {
		cout << "Student Not Found!" << endl;
		cout << "Please enter the Student ID of the student you wish to remove: ";
		while (!(cin >> id)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter the Student ID of the student you wish to remove: ";
		}
		select = sll0.findByID(id);
	}

	cout << "\nThe student to be removed is:" << endl;
	sll0.printOneStudent(select);

	if (!sll0.removeStudent(select))
		cout << "FAIL" << endl;

	cout << endl;
	sll0.printAllStudents();
	cout << "***** Current List Length: " << sll0.getListLength() << " *****" << endl;

	cout << string(60, '-') << endl << endl;

	cout << "Enter the name of the student you wish to insert " << s0->getStudentFN() << " after: ";
	cin >> name;
	select = sll0.findByName(name);
	while ((select == NULL) || (sll0.insertStudentAfterCheckH(select) == false) || (sll0.insertStudentAfterCheckT(select) == false)) {
		if (select == NULL)
			cout << "Student Not Found!" << endl;
		if (sll0.insertStudentAfterCheckH(select) == false) {
			cout << "Named student is in head node" << endl;
			cout << "Please choose a student not in the head or tail node" << endl;
		}
		if (sll0.insertStudentAfterCheckT(select) == false) {
			cout << "Named student is in tail node" << endl;
			cout << "Please choose a student not in the head or tail node" << endl;
		}
		cout << "Please enter the name of the student you wish to enter " << s0->getStudentFN() << " after: ";
		cin >> name;
		select = sll0.findByName(name);
	}
//	cout << "After while" << endl;
//	select = new StudentNode(s0.getStudentID(), s0.getStudentFN(), s0.getStudentGrade());
//	select = &s0;
//	cout << "After select" << endl;
	if(!sll0.insertStudentAfter(s0, name))
		cout << "\nFAIL" << endl;
//	cout << "after if" << endl;
	cout << endl;
	sll0.printAllStudents();
	cout << "***** Final List Length: " << sll0.getListLength() << " *****" << endl;
	cout << string(60, '-') << endl << endl;

//	sll0.~StudentLinkedList();
//	cout << "***** Destructors *****" << endl;
//	system("pause");
	return 0;
}