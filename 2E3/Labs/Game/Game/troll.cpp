#include <iostream>
#include <ctime>
#include "Races.h"
#include "troll.h"

using namespace std;

Troll::Troll() {
	srand((unsigned int)time(NULL));
	int check = getRand(100);
	if (check > 50) 
		Agility = 20 + getRand(60);
	else 
		Agility = 20 - getRand(5);
	check = getRand(100);
	if (check > 50)
		IQ = 30 + getRand(40);
	else 
		IQ = 30 - getRand(10);

	check = getRand(100);

	if (check > 50)
		Charisma = 30 + getRand(60);
	else
		Charisma = 30 - getRand(30);
	check = getRand(100);

	if (check > 50) {
		int test = getRand(15);
		Strength = 85 + test;
	}
	else {
		int test = getRand(15);
		Strength = 85 - test;
	}
	check = getRand(100);
	if (check > 50)
		Defend = 60 + getRand(35);
	else
		Defend = 60;
	check = getRand(100);;
	if (check > 50)
		Attack = 70 + getRand(25);
	else
		Attack = 70;
	Race = "Troll";
	Special = "Ironskin";
	Health = 100;
}