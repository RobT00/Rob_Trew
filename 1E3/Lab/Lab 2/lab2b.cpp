//Converts cm to yrds, ft and in. //
#include <iostream>

using namespace std;

int main() {
	double cm;
	int yrds, ft, in;
	
	cout << "Enter the centimetre value: ";
	cin >> cm ;
	
	cout << "You entered: " << cm << " cm" << endl;
	
	in = cm/2.54;
	yrds = in/36.0;
	in = in%36;
	ft = in/12.0;
	in = in%12;
	
	cout << "That is: " << yrds << " yrds, " << ft << " ft, and " << in << " in." << endl; 


	return 0;
};