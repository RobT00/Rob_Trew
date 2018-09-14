#pragma once
#include <iostream>
#include <string>
#include "npc_data.h"
#include "character.h"
#include "Races.h"

class NPC : public Races {
private:
	NPC_data* head;
	NPC_data* tail;
public:
	NPC();
	NPC(string, Races*);
	NPC(Character);
	void print_player();
	void printRace();
	void setHealth(int);
	string getRace();
	int getIQ();
	int getHealth();
	int getStrength();
	int getAttack();
	int getDefend();
	int getAgility();
	int getCharisma();
	string getSpecial();
};