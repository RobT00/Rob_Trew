#include <iostream>
#include <string>
#include "StudentNode.h"
#include "StudentLinkedList.h"

using namespace std;

StudentLinkedList::StudentLinkedList() {
	//headP = NULL;
	//tailP = NULL;
	root = NULL;
}

//StudentLinkedList::~StudentLinkedList() {
//	StudentNode* curr = headP;
//	StudentNode* next;
//	while (curr != NULL) {
//		next = curr->getNext();
//		headP->removedStudent();
//		delete curr;
//		curr = next;
//	}
//	if (getListLength() == 0) {
//		cout << "\nList deleted!" << endl;
//		cout << tailP->getDeleted() << " StudentNode(s), in total, deleted!" << endl;
//	}
//	cout << endl;
//}
//
//void StudentLinkedList::printAllStudents() {
//	StudentNode* currNode = headP;
//	cout << "***** Printing StudentLinkedList sll0 *****" << endl;
//	while (currNode != NULL) {
//		currNode->printStudent();
//		currNode = currNode->getNext();
//	}
//	cout << endl;
//}
//
//void StudentLinkedList::outputLinkedList(ofstream& file) {
//	StudentNode* currNode = headP;
//	while (currNode != NULL) {
//		currNode->outputStudent(file);
//		currNode = currNode->getNext();
//	}
//}

void StudentLinkedList::printOneStudent(StudentNode* currNode) {
	currNode->printStudent();
}

//StudentNode* StudentLinkedList::findByFName(string name) {
//	StudentNode* curr = headP;
//
//	while (curr != NULL) {
//		if (curr->getStudentFN() == name)
//			return curr;
//		curr = curr->getNext();
//	}
//	return curr;
//}
//
//StudentNode* StudentLinkedList::findByLName(string name) {
//	StudentNode* curr = headP;
//
//	while (curr != NULL) {
//		if (curr->getStudentLN() == name)
//			return curr;
//		curr = curr->getNext();
//	}
//	return curr;
//}
//
//StudentNode* StudentLinkedList::findByID(int s_id) {
//	StudentNode* curr = headP;
//
//	while (curr != NULL) {
//		if (curr->getStudentID() == s_id)
//			return curr;
//		curr = curr->getNext();
//	}
//	return curr;
//}

void StudentLinkedList::addStudent(string l, string f, int id, double grade) {
	StudentNode* newStudent = new StudentNode(l, f, id, grade);

	if (root == NULL) {
		root = newStudent;
		return;
	}
	StudentNode* insert = newStudent;
	StudentNode* curr = root;
	StudentNode* prev = root;

	while (curr != NULL) {
		prev = curr;
		if (insert->getStudentLN() == curr->getStudentLN()) {
			if (insert->getStudentFN() > curr->getStudentFN())
				curr = curr->getRight();
			else
				curr = curr->getLeft();
		}
		else if (insert->getStudentLN() > curr->getStudentLN())
			curr = curr->getRight();
		else {
			curr = curr->getLeft();
		}
	}
	if (insert->getStudentLN() == prev->getStudentLN()) {
		if (insert->getStudentFN() > prev->getStudentFN())
			prev->setRight(insert);
		else
			prev->setLeft(insert);
	}
	else if (insert->getStudentLN() > prev->getStudentLN()) {
		prev->setRight(insert);
	}
	else 
		prev->setLeft(insert);
}

//int StudentLinkedList::getListLength() {
//	return (tailP->getnumStudents());
//}
//
//int StudentLinkedList::checkListLength() {
//	StudentNode* curr = headP;
//	int checkL = 0;
//	while (curr != NULL) {
//		checkL++;
//		curr = curr->getNext();
//	}
//	return checkL;
//}

StudentNode* StudentLinkedList::findStudent(StudentNode* n, string l, string f) {
	if (n == NULL) {
		numberOfComparisons++;
		cout << "Student Not Found" << endl;
		cout << "Number of Comparisons: " << numberOfComparisons << endl;
		return NULL;
	}
	if ((n->getStudentLN() == l) && (n->getStudentFN() == f)) {
		numberOfComparisons++;
		cout << "Number of Comparisons: " << numberOfComparisons << endl;
		return n;
	}
	if (l == n->getStudentLN()) {
		numberOfComparisons++;
		if (n->getStudentFN() < f)
			return findStudent(n->getRight(), l, f);
		else
			return findStudent(n->getLeft(), l, f);
	}
	if (l < n->getStudentLN()) {
		numberOfComparisons++;
		return findStudent(n->getLeft(), l, f);
	}
	numberOfComparisons++;
	return findStudent(n->getRight(), l, f);
}

StudentNode* StudentLinkedList::findStudent(string l, string f) {
	numberOfComparisons = 0;
	return findStudent(root, l, f);
}