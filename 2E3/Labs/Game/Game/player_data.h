#pragma once
#include <iostream>
#include <string>
#include "Races.h"
using namespace std;

class Player_data : public Races{
private:
	Player_data* next;
public:
	Player_data();
	Player_data(string, int, int, int, int, int, int, int, string);
	Player_data* getNext() { return next; }
};