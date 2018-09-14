#include <iostream>
#include <string>
#include "character.h"
#include "NPC_data.h"
#include "NPC.h"

using namespace std;

NPC::NPC() {
	head = NULL;
	tail = NULL;
}

NPC::NPC(string input, Races* headP) {
	Races* curr = headP;
	while (curr) {
		if (curr->getRace() == input) {
			NPC_data* user = new NPC_data(curr->getRace(), curr->getHealth(), curr->getIQ(), curr->getStrength(), curr->getAttack(), curr->getDefend(), curr->getAgility(), curr->getCharisma(), curr->getSpecial());
			head = tail = user;
			return;
		}
		curr = curr->getNext();
	}
}

NPC::NPC(Character List) {
	Races* curr = List.getHead();
	NPC_data* user = new NPC_data(curr->getRace(), curr->getHealth(), curr->getIQ(), curr->getStrength(), curr->getAttack(), curr->getDefend(), curr->getAgility(), curr->getCharisma(), curr->getSpecial());
	head = tail = user;
}

void NPC::print_player() {
	NPC_data* curr = head;
	curr->print();
	cout << endl;
}

void NPC::printRace() {
	NPC_data* curr = head;
	curr->print_Race();
}

void NPC::setHealth(int amount) {
	NPC_data* curr = head;
	curr->changeHealth(amount);
}

string NPC::getRace() {
	NPC_data* curr = head;
	return (curr->getRace());
}

int NPC::getIQ() {
	NPC_data* curr = head;
	return (curr->getIQ());
}

int NPC::getHealth() {
	NPC_data* curr = head;
	return (curr->getHealth());
}

int NPC::getStrength() {
	NPC_data* curr = head;
	return (curr->getStrength());
}

int NPC::getAttack() {
	NPC_data* curr = head;
	return (curr->getAttack());
}

int NPC::getDefend() {
	NPC_data* curr = head;
	return (curr->getDefend());
}

int NPC::getAgility() {
	NPC_data* curr = head;
	return (curr->getAgility());
}

int NPC::getCharisma() {
	NPC_data* curr = head;
	return (curr->getCharisma());
}

string NPC::getSpecial() {
	NPC_data* curr = head;
	return (curr->getSpecial());
}
