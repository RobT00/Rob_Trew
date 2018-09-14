#include <iostream>
#include <string>
//#include "Student.h"
#include "StudentNode.h"
#include "StudentLinkedList.h"

using namespace std;

//int StudentLinkedList::length = 0;

StudentLinkedList::StudentLinkedList() {
	headP = NULL;
	tailP = NULL;
}

StudentLinkedList::~StudentLinkedList() {
//	cout << "\nStudentLinkedList Destructor" << endl;
	StudentNode* curr = headP;
	StudentNode* next;
	while (curr != NULL) {
		next = curr->getNext();
		headP->removedStudent();
		delete curr;
		curr = next;
//		cout << "DELETE" << endl;
	}
	if (getListLength() == 0) {
		cout << "\nList deleted!" << endl;
		cout << tailP->getDeleted() << " StudentNode(s), in total, deleted!" << endl;
	}
	cout << endl;
}

void StudentLinkedList::printAllStudents() {
	StudentNode* currNode = headP;
	cout << "***** Printing StudentLinkedList sll0 *****" << endl;
	while (currNode != NULL) {
		currNode->printStudent();
		/*cout << "Student Name: " << currNode->getStudentFN() << endl;
		cout << "Student ID: " << currNode->getStudentID() << endl;
		cout << "Final Grade: " << currNode->getStudentGrade() << endl << endl;*/
		currNode = currNode->getNext();
	}
	cout << endl;
}

void StudentLinkedList::printOneStudent(StudentNode* currNode) {
	currNode->printStudent();
	//cout << "Student Name: " << currNode->getStudentFN() << endl;
	//cout << "Student ID: " << currNode->getStudentID() << endl;
	//cout << "Final Grade: " << currNode->getStudentGrade() << endl << endl;
}

StudentNode* StudentLinkedList::findByName(string name) {
	StudentNode* curr = headP;

	while (curr != NULL) {
		if (curr->getStudentFN() == name)
			return curr;
		curr = curr->getNext();
	}
	return curr;
}

StudentNode* StudentLinkedList::findByID(int s_id) {
	StudentNode* curr = headP;

	while (curr != NULL) {
		if (curr->getStudentID() == s_id)
			return curr;
		curr = curr->getNext();
	}
	return curr;
}

void StudentLinkedList::addStudent(string name, double grade) {
	StudentNode* newStudent = new StudentNode(name, grade);
	if (tailP == NULL)
		headP = tailP = newStudent;
	else {
		tailP->setNext(newStudent);
		tailP = newStudent;
	}
//	headP->addedStudent();
	//	length++;
}

bool StudentLinkedList::removeStudent(string name) {
	StudentNode* curr = headP;
	StudentNode* prev = headP;
//	cout << name << endl;
	while (curr != NULL) {
//		cout << "tes" << endl;
//		cout << curr->getStudentFN() << endl;
		if (curr->getStudentFN() == name) {
//			cout << "curr = name" << endl;
			if (curr == headP) {
//				cout << "curr = head" << endl;
				headP = curr->getNext();
			}
			else {
				//cout << "1" << endl;
				//printAllStudents();
//				system("pause");
				prev->setNext(curr->getNext());
				//cout << "2" << endl;
				//printAllStudents();
//				system("pause");
//				cout << "Prev" << endl;
				if (curr == tailP) {
//					cout << "curr = tail" << endl;
					tailP = prev;
				}
			}
//			cout << "True" << endl;
			delete curr;
			headP->removedStudent();
			//length--;
			return true;
		}
		prev = curr;
		curr = curr->getNext();
	}
//	cout << "F" << endl;
	return false;
}

bool StudentLinkedList::removeStudent(int s_id) {
	StudentNode* curr = headP;
	StudentNode* prev = headP;

	while (curr != NULL) {
		if (curr->getStudentID() == s_id) {
			if (curr == headP)
				headP = curr->getNext();
			else {
				prev->setNext(curr->getNext());
				if (curr == tailP)
					tailP = prev;
			}
			delete curr;
			headP->removedStudent();
			return true;
		}
		prev = curr;
		curr = curr->getNext();
	}
	return false;
}

bool StudentLinkedList::removeStudent(StudentNode* select) {
	StudentNode* curr = select;
	StudentNode* prev = headP;
	if (prev != curr){
		while (prev->getNext() != curr) 
			prev = prev->getNext();
	}

	if (curr == headP) {
/*		cout << "curr = head" << endl*/;
		headP = curr->getNext();
	}
	else {
		//cout << "1" << endl;
		//printAllStudents();
		prev->setNext(curr->getNext());
//		system("pause");
		//cout << "2" << endl;
		//printAllStudents();
//		system("pause");
		if (curr == tailP) {
			//cout << "curr = tail" << endl;
			tailP = prev;
		}
	}
	//cout << "True" << endl;
	delete curr;
	headP->removedStudent();
	return true;
}

bool StudentLinkedList::insertStudentAfter(StudentNode* select, string name) {
	StudentNode* insert = select;
	StudentNode* prev = findByName(name);
	StudentNode* after = prev->getNext();
	insert->setNext(after);
	prev->setNext(insert);
//	cout << "check " << checkListLength() << endl;
//	cout << "act " << getListLength() << endl;
	if (checkListLength() == (getListLength() + 1)) {
		headP->addedStudent();
		//		length++;
		return true;
	}
	return false;
}

bool StudentLinkedList::insertStudentAfterCheckH(StudentNode* select) {
	if (select == headP)
		return false;

	return true;
}

bool StudentLinkedList::insertStudentAfterCheckT(StudentNode* select) {
	if (select == tailP)
		return false;

	return true;
}

int StudentLinkedList::getListLength() {
//	cout << "List L " << (tailP->getnumStudents()) << endl;
	return (tailP->getnumStudents());
	//	return length;
	//	return tailP->checknumS;
}

int StudentLinkedList::checkListLength() {
	StudentNode* curr = headP;
	int checkL = 0;
//	cout << "running" << endl;
	while (curr != NULL) {
		checkL++;
		curr = curr->getNext();
	}
	return checkL;
}