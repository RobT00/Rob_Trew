#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "npc.h"
#include "inventory.h"
#include "player.h"

using namespace std;

class Story {
private:
	ifstream output;
	string action, line;
	static bool dead, win;
	bool success;
	static int kills;
public:
	Story();
	void TellStory(Player, NPC, NPC, NPC, Inventory);
	void Scenario1(Player&, NPC&, Inventory&);
	void Scenario2(Player&, NPC&, Inventory&);
	void Scenario3(Player&, NPC&, NPC&, Inventory&, bool&);
	void battle(Player&, NPC&, Inventory&);
	void talk(Player&, NPC&, bool&, Inventory&);
	bool checkDead() { return dead; }
	bool checkWin() { return win; }
	int getKills() { return kills; }
	void printText(ifstream&, const Player);
	void endGame(Player&, Inventory&); 
	void heal(Player&, Inventory&);
};