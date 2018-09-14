#include <iostream>
#include <cmath>
using namespace std;

bool veryClose(double x, double y);

int main() {
    int yes=0;

	cout << "Is 5.00001 EQUAL to 5.00002?  ";
	if (5.00001 == 5.00002)
		cout << "Yes.\n";
	else cout << "No.\n";

	cout << "Is 5.00001 VERY CLOSE to 5.00002?  ";
	if (veryClose(5.00001, 5.00002))
		{cout << "Yes.\n";
		yes++;}
	else cout << "No.\n";
return yes;
}

bool veryClose (double x, double y) {
	//return true if the size of the difference between the numbers is less than 0.0001
	return (fabs(x-y) < 0.0001);
}
