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

void StudentLinkedList::outputLinkedList(ofstream& file) {
	StudentNode* currNode = headP;
	while (currNode != NULL) {
		currNode->outputStudent(file);
		currNode = currNode->getNext();
	}
}

void StudentLinkedList::printOneStudent(StudentNode* currNode) {
	currNode->printStudent();
}

StudentNode* StudentLinkedList::findByFName(string name) {
	StudentNode* curr = headP;

	while (curr != NULL) {
		if (curr->getStudentFN() == name)
			return curr;
		curr = curr->getNext();
	}
	return curr;
}

StudentNode* StudentLinkedList::findByLName(string name) {
	StudentNode* curr = headP;

	while (curr != NULL) {
		if (curr->getStudentLN() == name)
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

void StudentLinkedList::addStudent(string l, string f, int id, double grade) {
	StudentNode* newStudent = new StudentNode(l, f, id, grade);
	StudentNode* after = headP;
	StudentNode* curr = newStudent;
	if (headP == NULL) { //if list is empty
		//cout << "TEST1 " << curr->getStudentLN() << endl;
		headP = tailP = newStudent;
		//cout << "NEW LIST" << endl;
		//printAllStudents();
		return;
	}
	//cout << "A" << endl;
	//if (headP->getNext() != NULL) {
	//	cout << headP->getStudentLN() << endl;
	//	StudentNode* test = after->getNext();
	//	cout << test->getStudentLN() << endl;
	//}
	//cout << newStudent->getStudentLN() << endl;
	//cout << l << endl;
	//cout << "Q" << endl;
	//cout << curr->getStudentLN() << endl;
	//cout << after->getStudentLN() << endl;
	//cout << tailP->getnumStudents() << endl;
	if (curr->getStudentLN() < headP->getStudentLN()) {//New head
		//cout << "INsert at Head 1" << endl;
		if (tailP->getnumStudents() == 2) {
			after = tailP;
		}
		else {
			StudentNode* after2 = headP->getNext();
		}
		curr->setNext(after);
		//after->setNext(after2);
		headP = curr;
		//cout << "HEAD 1" << endl;
		//printAllStudents();
		return;
	}
	//cout << "B" << endl;
	if (curr->getStudentLN() == headP->getStudentLN()) {//Compare First Names
		//cout << "!!!!" << endl;
		if (curr->getStudentFN() < headP->getStudentFN()) {
			if (tailP->getnumStudents() == 2)
				after = tailP;
			else {
				StudentNode* after2 = headP->getNext();
			}
			//insertStudentAtHead(curr, headP);
			curr->setNext(after);
			headP = curr;
			//cout << "HEAD 2" << endl;
			//printAllStudents();
			return;
		}
		if ((tailP->getnumStudents() == 2) && (curr->getStudentFN() > after->getStudentFN())) {//make new tail node
			//cout << "HOHO" << endl;
			tailP->setNext(curr);
			tailP = curr;
			//printAllStudents();
			return;
		}
		if ((tailP->getnumStudents() == 2) && (curr->getStudentFN() == after->getStudentFN())) {
			//cout << "2 students, check IDs" << endl;
			if (curr->getStudentID() < after->getStudentID()) {
				//cout << "ID is less, new head, new tail" << endl;
				after = tailP;
				curr->setNext(after);
				headP = curr;
				return;
			}
			else {
				//cout << "ID is greater (or equal) same head, new tail " << endl;
				tailP->setNext(curr);
				tailP = curr;
				return;
			}
		}
		while ((after->getNext() != NULL) && (curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() > after->getStudentFN())) {
			//cout << "uhoh" << endl;
			//cout << curr->getStudentFN() << endl;
			//cout << after->getStudentFN() << endl;
			after = after->getNext();
			//cout << "1" << endl;
		}
		if (curr->getStudentFN() == after->getStudentFN()) {//First Names same, check IDs
			//cout << "Same" << endl;
			if (after->getNext() != NULL)
				//cout << "Next node not NULL" << endl;
			while ((after->getNext() != NULL) && (curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() == after->getStudentFN()) && (curr->getStudentID() > after->getStudentID()))
				after = after->getNext();
		}
		if (tailP->getnumStudents() == 3) {
			//cout << "Comparing IDs, 3 students" << endl;
			if (after == tailP) {
				//cout << "At tail" << endl;
				if (curr->getStudentID() > after->getStudentID()) {
					//cout << "ID is greater, setting new tail" << endl;
					//if (tailP->getnumStudents() == 3) {
					//	cout << "3 Students" << endl;

					//}
					headP->setNext(after);
					tailP->setNext(curr);
					tailP = curr;
					return;
				}
			}
			if (curr->getStudentID() < after->getStudentID()) {
				//cout << "Not at tail" << endl;
				if (after == headP) {
					//cout << "At head" << endl;
					headP = curr;
					curr->setNext(after);
					return;
				}
				//cout << "In middle" << endl;
				headP->setNext(curr);
				curr->setNext(after);
				return;
			}
		}
		if (after == headP) {
			//cout << "At head, >3 students" << endl;
			headP = curr;
			curr->setNext(after);
			return;
		}
		if (after == tailP) {
			//cout << "At tail, >3 students" << endl;
			//StudentNode* prev = headP;
			//while (prev->getNext() != tailP)
			//	prev = prev->getNext();
			//
			//prev->setNext(curr);
			//curr->setNext(after);
			//tailP = after;
			tailP->setNext(curr);
			tailP = curr;
			return;
		}
		//if (curr->getStudentID() > tailP->getStudentID()) {
		//	cout << "New tail in list with >2 students" << endl;
		//	if (tailP->getnumStudents() == 3) {
		//		cout << "3 students" << endl;
		//		headP->setNext(after);
		//		after->setNext(tailP);
		//	}
		//	else {
		//		StudentNode* prev = headP;
		//		while (prev->getNext() != tailP)
		//			prev = prev->getNext();
		//		prev->setNext(curr);
		//		curr->setNext(after);
		//		tailP = after;
		//		return;
		//}
		//cout << "2" << endl;
		insertStudentBefore(curr, after);
		//cout << "HEAD 3" << endl;
		//printAllStudents();
		return;
	}
	//if ((curr->getStudentLN() == after->getStudentLN()) && (tailP->getnumStudents() == 2)) {
	//	cout << "A!" << endl;
	//	if (curr->getStudentFN() < after->getStudentFN()) {
	//		cout << "TEST X " << endl;
	//		tailP = after;
	//		curr->setNext(after);
	//		return;
	//	}
	//	else {
	//		cout << "TEST Y" << endl;
	//		insertStudentAfter(curr, after);
	//		return;
	//	}
	//}

	//if ((curr->getStudentLN() == headP->getStudentLN()) && (curr->getStudentFN() < headP->getStudentFN())) {
	//	cout << "INsert at Head 2" << endl;
	//	if (tailP->getnumStudents() > 2) {
	//		StudentNode* after2 = headP->getNext();
	//		curr->setNext(after);
	//		//after->setNext(after2);
	//		headP = curr;
	//	}
	//	else {
	//		tailP = after;
	//		curr->setNext(after);
	//	}
	//	return;
	//}
	//
	//if ((curr->getStudentLN() == headP->getStudentLN()) && (curr->getStudentFN() >= headP->getStudentFN())) { //check to see if insert at head
	//	cout << "TEST  head " << curr->getStudentLN() << endl;
	//	//if (curr->getStudentFN() == headP->getStudentFN()) {
	//	//	insertStudentAfter(curr, headP->getStudentFN());
	//	//	return;
	//	//}
	//	while ((curr->getStudentFN() > after->getStudentFN()) && (after != NULL) && (curr->getStudentLN() == after->getStudentLN())) {
	//		if (curr->getStudentFN() == after->getStudentFN()) {
	//			insertStudentAfter(curr, after);
	//			return;
	//		}
	//		after = after->getNext();
	//	}
	//	insertStudentAfter(curr, after);
	//	return;
	//}
	//	if (curr->getStudentLN() == headP->getStudentLN()) {
	//		if (curr->getStudentFN() >= headP->getStudentFN()) {
	//			//insertStudentAfter(curr, headP->getStudentFN());
	//			insertStudentAfterHead(curr);
	//			cout << "yes" << endl;
	//			return;
	//		}
	//		else if (curr->getStudentFN() < headP->getStudentFN()) {
	//			int i = 0;
	//			while ((curr->getStudentFN() < after->getStudentFN()) && (curr->getStudentLN() == after->getStudentLN()) && (after != NULL)) {
	//				cout << "while " << endl;
	//				after = after->getNext();
	//				i++;
	//			}
	//			if (i > 1) {
	//				insertStudentAfter(curr, after->getStudentLN());
	//				return;
	//			}
	//			else {
	//				cout << "ELSE1" << endl;
	//				StudentNode* after2 = headP->getNext();
	//				curr->setNext(after);
	//				headP = curr;
	//				return;
	//			}
	//		}
	//		}
	//		else {
	//			cout << "ELSE2" << endl;
	//			StudentNode* after2 = headP->getNext();
	//			curr->setNext(after);
	//			//after->setNext(after2);
	//			headP = curr;
	//		}
	//		//StudentNode* select = findByLName(l);
	//		//if (select == headP) {
	//		//	cout << "SELECT" << endl;
	//		//	cout << l << endl;
	//		//	StudentNode* test = curr->getNext();
	//		//	cout << test->getStudentLN() << endl;
	//		//}
	//	//	cout << "TEST" << endl;
	//	//	cout << "TEST  " << newStudent->getStudentLN() << endl;
	//	//	if (headP->getNext() == NULL) {
	//	//		cout << "TEST  " << newStudent->getStudentLN() << endl;
	//	//		//StudentNode* node2;
	//	//		//node2->setNext(headP);
	//	//		//node2 = headP;
	//	//		//headP = node;
	//	//	}
	//	//	else {
	//	//		StudentNode* node2 = node->getNext();
	//	//		node2 = headP;
	//	//		headP = node;
	//	//	}
	//	//		prev = findByLName(headP->getStudentLN());
	//	//		after = prev->getNext();
	//	//		headP = newStudent;
	//	//		newStudent->setNext(after);
	//	//		StudentNode* insert = select;
	//	//		StudentNode* prev = findByLName(name);
	//	//		StudentNode* after = prev->getNext();
	//	//		insert->setNext(after);
	//	//		prev->setNext(insert);
	//	//	}
	//		return;
	//}
	//cout << "C" << endl;
	//if (tailP->getnumStudents() > 2)
	//	StudentNode* after = headP->getNext();
	while (after->getNext() != NULL) {//not adding to start of list, traverse
		//cout << "WHILE" << endl;
		//cout << curr->getStudentLN() << endl;
		//cout << after->getStudentLN() << endl;
		if (curr->getStudentLN() < after->getStudentLN()) {//add after head last name
			//cout << "INsert middle before 1" << endl;
			//cout << curr->getStudentLN() << endl;
			//cout << after->getStudentLN() << endl;
			insertStudentBefore(curr, after);
			//cout << "MIDDLE 1" << endl;
			//printAllStudents();
			return;
		}
		//if ((curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() == after->getStudentFN())) {
		//	//cout << "LAST AND FIRST EQUAL" << endl;
		//	//cout << "curr " << curr->getStudentLN() << curr->getStudentID() << curr->getStudentFN() << endl;
		//	//cout << "after " << after->getStudentLN() << after->getStudentID() << after->getStudentFN() << endl;
		//	if (curr->getStudentID() < after->getStudentID()) {
		//		insertStudentBefore(curr, after);
		//		return;
		//	}
		//	if (after->getNext() == NULL) {
		//		//cout << "ABOUT TO CRASH" << endl;
		//		//cout << "curr " << curr->getStudentLN() << curr->getStudentFN() << endl;
		//		//cout << "after " << curr->getStudentLN() << curr->getStudentFN() << endl;
		//		//cout << "tailP " << tailP->getStudentLN() << tailP->getStudentFN() << endl;
		//		//system("pause");
		//		if (curr->getStudentID() > after->getStudentID()) {
		//			StudentNode* link = headP;
		//			while (link->getNext() != after)
		//				link = link->getNext();
		//			tailP = curr;
		//			after->setNext(curr);
		//			link->setNext(after);
		//			return;
		//		}
		//		else {
		//			insertStudentAfter(curr, after);
		//			return;
		//		}
		//	}
		//	while ((after->getNext() != NULL) && (curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() == after->getStudentFN())) {
		//		if (curr->getStudentID() < after->getStudentID()) {
		//			insertStudentBefore(curr, after);
		//			return;
		//		}
		//		after = after->getNext();
		//	}
		//}
		if (curr->getStudentLN() == after->getStudentLN()) {//last names equal, checking first names
			//cout << "MIDDLE" << endl;
			if (curr->getStudentFN() < after->getStudentFN()) {
				insertStudentBefore(curr, after);
				return;
			}
			//else {
			//	while ((after->getNext() != NULL) && (curr->getStudentLN() == after->getStudentLN())) {
			//		if (curr->getStudentFN() < after->getStudentFN()) {
			//			insertStudentBefore(curr, after);
			//			return;
			//		}

			//	insertStudentAfter(curr, after);
			//	cout << "MIDDLE 2" << endl;
			//	//printAllStudents();
			//	return;
			//}
			//cout << "Student" << tailP->getnumStudents() << endl;
			while ((after->getNext() != NULL) && (curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() > after->getStudentFN())) {
				//cout << "uhoh" << endl;
				after = after->getNext();
				//if (after->getNext() == NULL) {
				//	cout << "FUCK" << endl;
				//	tailP->setNext(curr);
				//	tailP = curr;
				//	printAllStudents();
				//	return;
				//}
			}
			if (after->getNext() == NULL) {
				//cout << "ABOUT TO CRASH" << endl;
				//cout << "curr " << curr->getStudentLN() << curr->getStudentFN() << endl;
				//cout << "after " << curr->getStudentLN() << curr->getStudentFN() << endl;
				//cout << "tailP " << tailP->getStudentLN() << tailP->getStudentFN() << endl;
				//system("pause");
				StudentNode* link = headP;
				while (link->getNext() != after)
					link = link->getNext();
 				if (curr->getStudentFN() > after->getStudentFN()) {
					tailP = curr;
					after->setNext(curr);
					link->setNext(after);
					return;
				}
				else {
					link->setNext(curr);
					curr->setNext(tailP);
					return;
				}
			}
			if (curr->getStudentFN() == after->getStudentFN()) {//First Names same, check IDs
				//cout << "Same" << endl;
				while ((after->getNext() != NULL) && (curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() == after->getStudentFN()) && (curr->getStudentID() > after->getStudentID()))
					after = after->getNext();
			}
			//cout << "111" << endl;
			insertStudentBefore(curr, after);
			//cout << "MIDDLE 3" << endl;
			//printAllStudents();
			return;
		}
		//cout << "After " << after->getStudentLN() << after->getStudentFN() << endl;
		after = after->getNext();
		//cout << "AFTER" << endl;
		//cout << "Curr " << curr->getStudentLN() << curr->getStudentFN() << endl;
		//cout << "After " << after->getStudentLN() << after->getStudentFN() << endl;
		if (after->getNext() == NULL) {
			//cout << "XXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
			if ((curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() < after->getStudentFN())) {
				insertStudentBefore(curr, after);
				return;
			}
			if (curr->getStudentLN() < after->getStudentLN()) {
				//cout << "Test" << endl;
				insertStudentBefore(curr, after);
				return;
			}
		}
	}
		//if ((curr->getStudentLN() == after->getStudentLN()) && (curr->getStudentFN() >= after->getStudentFN())) {
		//	cout << "TEST  insert before " << curr->getStudentLN() << curr->getStudentFN() << endl;
		//	if (curr->getStudentFN() == after->getStudentFN()) {
		//		insertStudentAfter(curr, after->getStudentLN()); //then check id?
		//		return;
		//	}
		//	while ((curr->getStudentFN() > after->getStudentFN()) && (after != NULL) && (curr->getStudentLN() == after->getStudentLN())) {
		//		if (curr->getStudentFN() == after->getStudentFN()) {
		//			insertStudentAfter(curr, after->getStudentLN());
		//			return;
		//		}
		//		after = after->getNext();
		//	}
		//	cout << "after while " << curr->getStudentLN() << curr->getStudentFN() << endl;
		//	insertStudentAfter(curr, after->getStudentLN());
		//	return;
		//}
		//cout << "TEST  middle " << curr->getStudentLN() << curr->getStudentFN() << endl;
		//cout << after->getStudentLN() << after->getStudentFN() << endl;
		//if (curr->getStudentLN() <= after->getStudentLN()) {
		//	cout << "TEST 1 " << endl;
		//	while ((curr->getStudentFN() > after->getStudentFN()) && (curr->getStudentLN() == after->getStudentLN()) && (after !=NULL)) {
		//		cout << "TEST 3" << endl;
		//		after = after->getNext();
		//		cout << "1" << endl;
		//	}
		//	cout << "ater" << endl;
		//	insertStudentBefore(curr, after->getStudentLN());
		//	return;
		//}
			//else {
			//	cout << "ELSE" << endl;
			//	cout << "CURR " << curr->getStudentLN() << endl;
			//	cout << "AFTER " << after->getStudentLN() << endl;
			//	insertStudentBefore(curr, after->getStudentFN());
			//	//printAllStudents();
			//	return;
			//	//break;
			//}


	//insert at tail
	//cout << "TEST  tail " << curr->getStudentLN() << curr->getStudentFN() << endl;
	//cout << "Current Tail " << tailP->getStudentLN() << tailP->getStudentFN() << endl;
	//cout << "After " << after->getStudentLN() << after->getStudentFN() << endl;
	tailP->setNext(curr);
	tailP = curr;
	//printOneStudent(headP);
	//printOneStudent(headP->getNext());
	//cout << "TAIL" << endl;
	//printAllStudents();
	return;
}

//void StudentLinkedList::addStudent(string l, string f, int id, double grade) {
//	StudentNode* newStudent = new StudentNode(l, f, id, grade);
//	if (tailP == NULL) {
//		headP = tailP = newStudent;
//		//pointer = headP;
//	}
//	else {
//		tailP->setNext(newStudent);
//		tailP = newStudent;
//	}
//}

//StudentNode* StudentLinkedList::addStudent(StudentNode* place, string l, string f, int id, double grade) {
//	StudentNode* prev = nullptr;
//	StudentNode* curr = place;
//
//	while (curr && !(l < curr->getStudentLN())) {
//		while (curr && !(f < curr->getStudentLN())) {
//			prev = curr;
//			curr = curr->getNext();
//		}
//	}
//	if (prev == nullptr)
//		place = new StudentNode(l, f, id, grade);
//	else {
//		prev = prev->getNext();
//		prev = new StudentNode(l, f, id, grade);
//	}
//	return place;
//}

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

bool StudentLinkedList::insertStudentAfter(StudentNode* select, StudentNode* curr) {
	StudentNode* insert = select;
	StudentNode* prev = curr;
	StudentNode* after = prev->getNext();
	insert->setNext(after);
	prev->setNext(insert);
	if (checkListLength() == (getListLength() + 1)) {
		headP->addedStudent();
		return true;
	}
	return false;
}

void StudentLinkedList::insertStudentAtHead(StudentNode* newH, StudentNode* oldH) {
	//cout << "OldH1" << oldH->getStudentLN() << oldH->getStudentFN() << endl;
	//oldH = oldH->getNext();
	//cout << "OldH2" << oldH->getStudentLN() << oldH->getStudentFN() << endl;
	//cout << "NewH 1" << newH->getStudentLN() << newH->getStudentFN() << endl;
	newH->setNext(oldH);
	headP = newH;
	//cout << "HEAD" << headP->getStudentLN() << headP->getStudentFN() << endl;
	//cout << headP->getNext()->getStudentLN() << headP->getNext()->getStudentFN() << endl;
}

//bool StudentLinkedList::insertStudentAfterSpecial(StudentNode* select, string name) {
//	StudentNode* insert = select;
//	StudentNode* prev = findByFName(name);
//	StudentNode* after = prev->getNext();
//	insert->setNext(after);
//	prev->setNext(insert);
//	if (checkListLength() == (getListLength() + 1)) {
//		headP->addedStudent();
//		return true;
//	}
//	return false;
//}
//
//bool StudentLinkedList::insertStudentBeforeSpecial(StudentNode* select, string name) {
//	StudentNode* insert = select;
//	StudentNode* after = findByLName(name);
//	StudentNode* prev = headP;
//	while (prev != NULL) {
//		if (prev->getNext()->getStudentLN() == name)
//			break;
//		prev = prev->getNext();
//	}
//	prev->setNext(insert);
//	insert->setNext(after);
//	if (checkListLength() == (getListLength() + 1)) {
//		headP->addedStudent();
//		return true;
//	}
//	return false;
//}


bool StudentLinkedList::insertStudentAfterHead(StudentNode* select) {
	StudentNode* insert = select;
	StudentNode* after = headP->getNext();
	StudentNode* prev = headP;
	insert->setNext(after);
	prev->setNext(insert);
	if (checkListLength() == (getListLength() + 1)) {
		headP->addedStudent();
		return true;
	}
	return false;
}

bool StudentLinkedList::insertStudentBefore(StudentNode* select, StudentNode* curr) {
	StudentNode* insert = select;
	StudentNode* after = curr;
	StudentNode* prev = headP;
	while (prev != NULL) {
		if (prev->getNext() == curr)
			break;
		prev = prev->getNext();
	}
	prev->setNext(insert);
	insert->setNext(after);
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

StudentNode* StudentLinkedList::findStudent(string l, string f) {//names ordered first, last, ID
	numberOfComparisons = 0;
	StudentNode* curr1, *curr2;
	curr1 = curr2 = headP;
	//if (curr1 != NULL) {
	//	curr2 = curr1;
	//	if ((curr1->getStudentLN() == l) && (curr2->getStudentFN() == f)) {
	//		return curr2;
	//	}
	//	else {
	//		while ((curr2 != NULL) && (curr2->getStudentLN() == l)) {
	//			curr2 = curr2->getNext();
	//			if ((curr1->getStudentLN() == l) && (curr2->getStudentFN() == f)) {
	//				return curr2;
	//			}
	//		}
	//	}
	//}
	//	curr2 = findByFName(f);
	//	if (curr2 != NULL)
	//		if (curr1 == curr2)
	//			return curr1;
	//}
	//else
	if (headP->getStudentLN() > l) {
		numberOfComparisons++;
		cout << "Number of Comparisons: " << numberOfComparisons << endl;
		return NULL;
	}
	while (curr1 != NULL) {
		numberOfComparisons++;
		if (curr1->getStudentLN() == l) {
			//numberOfComparisons++;
			curr2 = curr1;
			if (curr2->getStudentFN() == f) {
				numberOfComparisons++;
				cout << "Number of Comparisons: " << numberOfComparisons << endl;
				return curr2;
			}
			else {
				while ((curr1 != NULL) && (curr2 != NULL) && (curr1->getStudentLN() == l)) {
					if (curr2->getStudentFN() == f) {
						//numberOfComparisons++;
						cout << "Number of Comparisons: " << numberOfComparisons << endl;
						return curr2;
					}
					if ((curr2->getStudentFN() > f)){
						cout << "Number of Comparisons: " << numberOfComparisons << endl;
						return NULL;
					}
					curr1 = curr1->getNext();
					curr2 = curr2->getNext();
					numberOfComparisons++;
				}
			}
		}
		if (((curr1->getStudentLN())[0] > l[0]) && ((curr1->getStudentFN()[1] > l[1]))) {
			if (numberOfComparisons == 0)
				numberOfComparisons++;
			cout << "Number of Comparisons: " << numberOfComparisons << endl;
			return NULL;
		}
		curr1 = curr1->getNext();
	}
	cout << "Number of Comparisons: " << numberOfComparisons << endl;
	return NULL;
}