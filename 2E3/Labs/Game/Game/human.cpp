#include <iostream>
#include <ctime>
#include "Races.h"
#include "human.h"

using namespace std;

Human::Human() {
	srand((unsigned int)time(NULL));
	Agility = 50 + getRand(5);
	Attack = 50;
	int check = getRand(100);
	if (check > 50) {
		int test = getRand(40);
		IQ = 60 + test;
	}
	else {
		int test = getRand(15);
		IQ = 60 - test;
	}
	Strength = 50;
	Defend = 50;
	Charisma = 80 + getRand(20);
	Race = "Human";
	Special = "Scavenger";
	Health = 100;
}