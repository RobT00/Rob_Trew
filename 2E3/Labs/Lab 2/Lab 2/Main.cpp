#include <iostream>
#include <string>
#include "coordinates.h"
#include "rect.h"

using namespace std;

Rect readIN();
void printRects(Rect r1, Rect r2);

int main() {
	string answer;
	cout << "Would you like to use custom values? ";
	cin >> answer;
	cout << endl;
	if (answer == "N" || answer == "n") {
		Rect r1(1, 2, 3, 1);

		Coordinates topLeft(2, 3);
		Coordinates bottomRight(4, 1);
		Rect r2(topLeft, bottomRight);
		printRects(r1, r2);
	}
	else if (answer != "n") {
		cout << "Rectangle 1 " << endl;
		Rect r1 = readIN();
		cout << "Rectangle 2 " << endl;
		Rect r2 = readIN();
		printRects(r1, r2);
	}
	
	return 0;
}

Rect readIN() {
	int top, Left, bottom, Right;
	int i = 0;
	cout << "Please enter the following coordinates: \n\n";
	while (i < 2) {
		cout << "Top left ";
		if (i == 0) {
			cout << "X: ";
			cin >> Left;
		}
		else {
			cout << "Y: ";
			cin >> top;
		}
		i++;
	}
	cout << endl;
	i = 0;
	while (i < 2) {
		cout << "Bottom right ";
		if (i == 0) {
			cout << "X: ";
			cin >> Right;
		}
		else {
			cout << "Y: ";
			cin >> bottom;
		}
		i++;
	}
	cout << endl;
	
	return Rect(Left, top, Right, bottom);
}

void printRects(Rect r1, Rect r2) {
	cout << "Rectange 1: " << endl;
	r1.print();
	cout << endl << "Rectangle 2: " << endl;
	r2.print();
	cout << endl;
	cout << "Union Rectangle: " << endl;
	r1.findUnion(r2).print();
	cout << endl;
}
