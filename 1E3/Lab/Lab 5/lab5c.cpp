#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main () {
	int number, integer, prev = 0, current = 1, next, terms =0;
	
	cout << "Enter an integer: ";
	cin >> number;
	integer = 0;
	while (next<number)
	{
		if (integer<=1)
		{
			cout << integer << endl;
			integer++;
			terms++;
		}
		
		else
		{
			next = prev + current;
			prev = current;	
			current = next;
			integer++;
			if (next<number)
			{
				cout << next << endl;
				terms++;
			}
			else
				break;
		}	
		
		
	}
	cout << "Number of terms = " << terms;
	cout << endl;
	
	return 0;
}