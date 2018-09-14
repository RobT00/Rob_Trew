#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main () {
	int number, integer, prev = 0, current = 1, next;
	
	cout << "Enter a small integer: ";
	cin >> number;
	
	for (integer=0;integer<number;integer++)
	{
		if (integer<=1)
			cout << integer << endl;
		
		else
		{
			next = prev + current;
			prev = current;	
			current = next;
			cout << next << endl;
		}	
	}
	cout << endl;
	
	return 0;
}