#pragma once
#include "coordinates.h"

class Rect {
public:
	int Left, top, Right, bottom; //Attributes

	//Method
	Rect(); //Default Constructor
	Rect(Coordinates, Coordinates);
	Rect(int , int, int, int);

	int area();
	Rect findUnion(Rect );
	void print();
};