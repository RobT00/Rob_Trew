#pragma once
#include <iostream>
#include <string>

using namespace std; 

class Races {
private:
	Races* next;
protected:
	string Race, Special;
	int IQ, Strength, Attack, Defend, Agility, Charisma, Health;
public:
	Races();
	Races(string, int, int, int, int, int, int, int, string);
	string getRace() { return Race; }
	int getIQ() { return IQ; }
	int getHealth() { return Health; }
	int getStrength() { return Strength; }
	int getAttack() { return Attack; }
	int getDefend() { return Defend; }
	int getAgility() { return Agility; }
	int getCharisma() { return Charisma; }
	string getSpecial() { return Special; }
	Races* getNext() { return next; }
	void setNext(Races* _next) { next = _next; }
	void getAttributes(Races*, string&, int&, int&, int&, int&, int&, int&, int&, string&);
	void print();
	void print_Race() {cout << Race << endl; }
	int getRand(int lim);
	void changeHealth(int amt) { Health = amt; }
};