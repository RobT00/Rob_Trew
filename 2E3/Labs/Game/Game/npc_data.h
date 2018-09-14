#pragma once
#include <iostream>
#include <string>
#include "Races.h"
using namespace std;

class NPC_data : public Races {
private:
	NPC_data* next;
public:
	NPC_data();
	NPC_data(string, int, int, int, int, int, int, int, string);
	NPC_data* getNext() { return next; }
};