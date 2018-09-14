#include <iostream>
#include <string>
#include "character.h"
#include "player_data.h"
#include "player.h"

using namespace std;

Player::Player() {
	head = NULL;
	tail = NULL;
}

Player::Player(string input, Races* headP) {
	Races* curr = headP;
	while (curr) {
		if (curr->getRace() == input) {
			Player_data* user = new Player_data(curr->getRace(), curr->getHealth(), curr->getIQ(), curr->getStrength(), curr->getAttack(), curr->getDefend(), curr->getAgility(), curr->getCharisma(), curr->getSpecial());
			head = tail = user;
			return;
		}
		curr = curr->getNext();
	}
}

string Player::getRace() {
	Player_data* curr = head;
	return (curr->getRace());
}

int Player::getIQ() {
	Player_data* curr = head;
	return (curr->getIQ());
}

int Player::getHealth() {
	Player_data* curr = head;
	return (curr->getHealth());
}

int Player::getStrength() {
	Player_data* curr = head;
	return (curr->getStrength());
}

int Player::getAttack() {
	Player_data* curr = head;
	return (curr->getAttack());
}

int Player::getDefend() {
	Player_data* curr = head;
	return (curr->getDefend());
}

int Player::getAgility() {
	Player_data* curr = head;
	return (curr->getAgility());
}

int Player::getCharisma() {
	Player_data* curr = head;
	return (curr->getCharisma());
}

string Player::getSpecial() {
	Player_data* curr = head;
	return (curr->getSpecial());
}

void Player::print_player() {
	Player_data* curr = head;
	curr->print();
	cout << endl;
}

void Player::printRace() {
	Player_data* curr = head;
	curr->print_Race();
}

void Player::setHealth(int amount) {
	Player_data* curr = head;
	curr->changeHealth(amount);
}

void Player::takePotion(Inventory& potion) {
	potion.usePotion();
	setHealth(100);
}