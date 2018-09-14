#pragma once
#include <iostream>
#include "inventory_data.h"

using namespace std;

class Inventory : public Inventory_data {
private:
	Inventory_data* head;
	Inventory_data* tail;
public:
	Inventory();
	void print();
	void foundBow();
	void foundSword();
	void foundStaff();
	void addGold(int);
	void addPotion(int);
	void spendGold(int);
	void usePotion();
	void fillBag();
};