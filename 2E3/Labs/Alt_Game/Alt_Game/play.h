#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "check.h"

using namespace std;

class Play : public Check{
private:
	static int score;
	static int lines;
	ifstream quiz;
	string line;
protected:
	string *questions;
	string *answers;
public:
	Play();
	void printQ();
	void printA();
	void game();
	void end();
};
