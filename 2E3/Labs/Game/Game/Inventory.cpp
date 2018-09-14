#include <iostream>
#include "inventory.h"

using namespace std;

Inventory::Inventory() {
	head = NULL;
	tail = NULL;
	fillBag();
}

void Inventory::fillBag() {
	Inventory_data* bag = new Inventory_data();
	head = tail = bag;
}

void Inventory::print() {
	Inventory_data* curr = head;
	while (curr) {
		curr->print_items();
		curr = curr->getNext();
	}
	cout << endl;
}

void Inventory::foundBow() {
	bow = true;
}

void Inventory::foundStaff() {
	staff = true;
}

void Inventory::foundSword() {
	sword = true;
}

void Inventory::addGold(int amount) {
	gold = gold + amount;
}

void Inventory::addPotion(int amount) {
	potion += amount;
}

void Inventory::spendGold(int amount) {
	gold = gold - amount;
}

void Inventory::usePotion() {
	potion -= 1;
}