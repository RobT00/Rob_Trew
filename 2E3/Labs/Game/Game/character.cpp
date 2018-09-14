#include <iostream>
#include <string>
#include <ctime>
#include "character.h"
#include "Screen.h"

using namespace std;

Character::Character() {
	head = NULL;
	tail = NULL;
	addRace();
}

void Character::printList() {
	Races* curr = head;
	if (!curr) {
		cout << "List empty!" << endl;
		screen << "List empty!" << endl;
	}
	while (curr) {;
		curr->print();
		curr = curr->getNext();
		cout << endl;
	}
}

void Character::addRace() {
	Races* add = new Races(Elf());
	head = tail = add;
	
	add = new Races(Human());
	tail->setNext(add);
	tail = add;

	add = new Races(Troll());
	tail->setNext(add);
	tail = add;

	add = new Races(Wizard());
	tail->setNext(add);
	tail = add;
}

void Character::remove1(string race) {
	Races* curr = head;
	Races* prev = head;

	if (head->getRace() == race) {
		prev = prev->getNext();
		head = prev;
		prev->setNext(prev->getNext());
		delete curr;
		return;
	}
	while (curr->getRace() != race)
		curr = curr->getNext();
	while (prev->getNext() != curr) 
		prev = prev->getNext();
	if (curr == tail) {
		delete curr;
		tail = prev;
		prev->setNext(NULL);
		return;
	}
	else {
		if (prev == head) {
			head->setNext(curr->getNext());
		}
		else 
			prev->setNext(curr->getNext());
	}
	delete curr;
}

void Character::remove2(Races* curr) {
	Races* prev = curr;
	if ((curr == head) && (curr == tail)){
		delete curr;
		head = tail = NULL;
		return;
	}
	else if (curr = head) {
		prev = prev->getNext();
		delete curr;
		head = prev;
		return;
	}
	else if (curr == tail) {
		delete curr;
		tail = prev;
		prev->setNext(NULL);
		return;
	}
	else {
	while (prev->getNext() != curr)
		prev = prev->getNext();
		if (prev == head) {
			head->setNext(curr->getNext());
		}
		else
			prev->setNext(curr->getNext());
	}
	delete curr;
}