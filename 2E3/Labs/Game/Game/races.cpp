#include <iostream>
#include <string>
#include <ctime>
#include "Races.h"
#include "Screen.h"

using namespace std;

Races::Races() {
	next = NULL;
}

Races::Races(string race, int health, int iq, int strength, int attack, int defend, int agility, int charisma, string special) {
	Race = race;
	IQ = iq;
	Strength = strength;
	Attack = attack;
	Defend = defend;
	Agility = agility;
	Charisma = charisma;
	Special = special;
	Health = health;
	next = NULL;
}

void Races::print() {
	cout << "Race: " << Race << endl;
	screen << "Race: " << Race << endl;
	cout << "Health: " << Health << "/100" << endl;
	screen << "Health: " << Health << "/100" << endl;
	cout << "Agility: " << Agility << endl;
	screen << "Agility: " << Agility << endl;
	cout << "IQ: " << IQ << endl;
	screen << "IQ: " << IQ << endl;
	cout << "Attack: " << Attack << endl;
	screen << "Attack: " << Attack << endl;
	cout << "Strength: " << Strength << endl;
	screen << "Strength: " << Strength << endl;
	cout << "Defend: " << Defend << endl;
	screen << "Defend: " << Defend << endl;
	cout << "Charisma: " << Charisma << endl;
	screen << "Charisma: " << Charisma << endl;
	cout << "Special: " << Special << endl;
	screen << "Special: " << Special << endl;
}

void Races::getAttributes(Races* curr, string& race, int& health, int& iq, int& strength, int& attack, int& defend, int& agility, int& charisma, string& special) {
	race = Race;
	health = Health;
	iq = IQ;
	strength = Strength;
	attack = Attack;
	defend = Defend;
	agility = Agility;
	charisma = Charisma;
	special = Special;
}

int Races::getRand(int lim) {
	srand((unsigned int)time(NULL));
	return (rand() % lim + 1);
}