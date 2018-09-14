#pragma once
#include <iostream>
#include <string>
#include "character.h"
#include "Races.h"
#include "inventory.h"
#include "npc.h"
#include "player_data.h"

class Player : public Races{
private:
	Player_data* head;
	Player_data* tail;
public:
	Player();
	Player(string, Races*);
	string getRace();
	int getIQ();
	int getHealth();
	int getStrength();
	int getAttack();
	int getDefend();
	int getAgility();
	int getCharisma();
	string getSpecial();
	void print_player();
	void printRace();
	void setHealth(int);
	void takePotion(Inventory&);
};