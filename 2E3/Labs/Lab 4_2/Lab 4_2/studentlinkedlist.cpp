#include <iostream>
#include <string>
#include "StudentNode.h"
#include "StudentLinkedList.h"

using namespace std;

StudentLinkedList::StudentLinkedList() {
	headP = NULL;
	tailP = NULL;
}

StudentLinkedList::~StudentLinkedList() {
	StudentNode* curr = headP;
	StudentNode* next;
	while (curr != NULL) {
		next = curr->getNext();
		headP->removedStudent();
		delete curr;
		curr = next;
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
		currNode = currNode->getNext();
	}
	cout << endl;
}

void StudentLinkedList::printOneStudent(StudentNode* currNode) {
	currNode->printStudent();
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
	if (headP == NULL)
		headP = tailP = newStudent;
	else {
		tailP->setNext(newStudent);
		tailP = newStudent;
	}
}

bool StudentLinkedList::removeStudent(string name) {
	StudentNode* curr = headP;
	StudentNode* prev = headP;
	while (curr != NULL) {
		if (curr->getStudentFN() == name) {
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
	if (prev != curr) {
		while (prev->getNext() != curr)
			prev = prev->getNext();
	}
	cout << "CURR " << curr->getStudentFN() << endl;
	cout << "PREV " << prev->getStudentFN() << endl;
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

bool StudentLinkedList::insertStudentAfter(StudentNode* select, string name) {
	StudentNode* insert = select;
	StudentNode* prev = findByName(name);
	StudentNode* after = prev->getNext();
	insert->setNext(after);
	prev->setNext(insert);
	if (checkListLength() == (getListLength() + 1)) {
		headP->addedStudent();
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
	return (tailP->getnumStudents());
}

int StudentLinkedList::checkListLength() {
	StudentNode* curr = headP;
	int checkL = 0;
	while (curr != NULL) {
		checkL++;
		curr = curr->getNext();
	}
	return checkL;
}