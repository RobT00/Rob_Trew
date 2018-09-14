//Gives pizza value in price per square inch //
#include <iostream>
#include <cmath>
using namespace std;

int main() {	
	int diameter;
	double price;
	
	cout << "Enter Diameter of Pizza:";
	cin >> diameter;
	cout << "Enter Price of Pizza:";
	cin >> price;
	cout << "You entered:" << diameter << "inches and" << price << "euros.\n";
	
	double area, radius;
	radius = diameter/2.0;
	area = M_PI*radius*radius;
	
	cout << "The Area of the Pizza is:" << area << endl;
	cout << "The Price per Square Inch is:" << (price/area)*100 << " cent." << endl;
	
	return 0;
};