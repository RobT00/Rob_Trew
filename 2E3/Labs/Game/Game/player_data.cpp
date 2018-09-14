#include <iostream>
#include <string>
#include "player_data.h"

using namespace std;

Player_data::Player_data() {
	next = NULL;
}

Player_data::Player_data(string race, int health, int iq, int strength, int attack, int defend, int agility, int charisma, string special) {
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