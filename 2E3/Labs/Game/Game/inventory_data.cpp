#include <iostream>
#include <string>
#include <fstream>
#include "inventory_data.h"
#include "Screen.h"

using namespace std;

bool Inventory_data::bow = false;
bool Inventory_data::sword = false;
bool Inventory_data::staff = false;
int Inventory_data::gold = 10;
int Inventory_data::potion = 1;

Inventory_data::Inventory_data() {
	next = NULL;
}

void Inventory_data::print_items() {
	cout << "Gold: " << gold << endl;
	screen << "Gold: " << gold << endl;
	cout << "Potions: " << potion << endl;
	screen << "Potions: " << potion << endl;
	cout << "Bow: ";
	screen << "Bow: ";
	if (bow) {
		cout << "Yes" << endl;
		screen << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
		screen << "No" << endl;
	}
	cout << "Sword: ";
	screen << "Sword: ";
	if (sword) {
		cout << "Yes" << endl;
		screen << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
		screen << "No" << endl;
	}
	cout << "Staff: ";
	screen << "Staff: ";
	if (staff) {
		cout << "Yes" << endl;
		screen << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
		screen << "No" << endl;
	}
}