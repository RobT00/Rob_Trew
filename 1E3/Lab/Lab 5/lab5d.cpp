#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main () {
	short integer, prev = 0, current = 1, next, terms =0;
	
	
	integer = 0;
	next = 0;
	while (next>=0)
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
			if (next>0)
			{
				cout << next << endl;
				terms++;
			}
			else
				break;
		}	
		
		
	}
	cout << "Number of terms to break code = " << terms;
	cout << endl;
	
	return 0;
}