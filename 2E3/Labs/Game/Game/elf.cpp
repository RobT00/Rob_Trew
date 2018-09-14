#include <iostream>
#include <ctime>
#include "Races.h"
#include "elf.h"

using namespace std;

Elf::Elf() {
	srand((unsigned int)time(NULL));
	Agility = 75 + getRand(25);
	IQ = 50 + getRand(50);
	int check = getRand(100);
	if (check > 50) {
		int test = getRand(55);
		Attack = 45 + test;
	}
	else {
		int test = getRand(15);
		Attack = 45 - test;
	}
	Strength = 30;
	Defend = 50;
	Charisma = 40;
	Special = "Dodge";
	Race = "Elf";
	Health = 100;
}
