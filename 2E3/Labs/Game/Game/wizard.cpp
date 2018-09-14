#include <iostream>
#include <ctime>
#include "Races.h"
#include "wizard.h"

using namespace std;

Wizard::Wizard() {
	srand((unsigned int)time(NULL));
	IQ = 80;
	Agility = 40;
	if (getRand(100) > 50)
		Charisma = 40 + getRand(10);
	else
		Charisma = 40;
	Strength = 20;
	Defend = 50;
	Attack = 55;
	Race = "Wizard";
	Special = "Magic";
	Health = 100;
}