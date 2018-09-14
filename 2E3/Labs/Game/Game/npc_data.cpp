#include <iostream>
#include <string>
#include "npc_data.h"

using namespace std;

NPC_data::NPC_data() {
	next = NULL;
}

NPC_data::NPC_data(string race, int health, int iq, int strength, int attack, int defend, int agility, int charisma, string special) {
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
