#include "rect.h"
#include "coordinates.h"
#include <math.h>
#include <iostream>

using namespace std;

//Constructor Definitions
Rect::Rect() { //Default constructor
	Left = top = Right = bottom = 0; //Assigning 0
}

Rect::Rect(Coordinates c0, Coordinates c1) { 
	Left = c0.x;
	top = c0.y;
	Right = c1.x;
	bottom = c1.y;
}

Rect::Rect(int x0, int y0, int x1, int y1) {
	Left = x0;
	top = y0;
	Right = x1;
	bottom = y1;
}

//Methods
int Rect::area() { 
	return (abs(Left - Right) * abs(top - bottom));
}

//Finding top and bottom coordinates
int max(int a, int b) {
	if (a < b)
		return b;
	return a;
}
int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

Rect Rect::findUnion(Rect r2) {
	int topLeftX, topLeftY, bottomRightX, bottomRightY;
	topLeftX = min(Left, r2.Left);
	topLeftY = max(top, r2.top);
	bottomRightX = max(Right, r2.Right);
	bottomRightY = (bottom, r2.bottom);
	return Rect(topLeftX, topLeftY, bottomRightX, bottomRightY);
}

void Rect::print() {
	cout << "Top Left: (" << Left << " , " << top << ") " << endl;
	cout << "Bottom Right: (" << Right << " , " << bottom << ") " << endl;

	cout << "Area: " << area() << " sq. units" << endl;
}

