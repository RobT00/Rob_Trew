#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Check {
private:
	bool win;
public:
	Check();
	bool compare(string&, string&);
};