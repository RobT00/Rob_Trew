#pragma once
#include <iostream>
#include <string>

using namespace std;

class Inventory_data {
private:
	Inventory_data* next;
protected:
	static bool bow, sword, staff;
	static int gold, potion;
public:
	Inventory_data();
	Inventory_data* getNext() { return next; }
	void setNext(Inventory_data* _next) { next = _next; }
	int getGold() { return gold; }
	int getPotion() { return potion; }
	bool checkBow() { return bow; }
	bool checkSword() { return sword; }
	bool checkStaff() { return staff; }
	void print_items();
};