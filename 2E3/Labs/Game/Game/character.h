#pragma once
#include <iostream>
#include <string>
#include "Races.h"
#include "elf.h"
#include "human.h"
#include "troll.h"
#include "wizard.h"

using namespace std;

class Character{
private:
	Races* head;
	Races* tail;
public:
	Character();
	Races* getHead() { return head; }
	void printList();
	void addRace();
	void remove1(string);
	void remove2(Races*);
};