#pragma once
#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

class Module {
private:
	static const int SIZE = 5;
	Student students[SIZE];

public:
	
	void readallMarks();
	void printallGrades();

	int findByName(string );
	string findByID(int );
};