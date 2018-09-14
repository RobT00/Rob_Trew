#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main () {
	double invest, rate, i, j, brackets, power, net;
	int yrs=30;
	
	cout << "Enter in Investment: ";
	cin >> invest;
	
 	cout << "Rate" << setw(5) << "|";
 	for (i=5;i<=yrs;i=i+5) {
 		cout << setw(10) << i << " years";
 	}
 	cout << endl;
 	cout << std::fixed << setprecision(2);
 	for (i=0; i<=105; i++){
 		cout <<"-";
 	}
 	cout << endl;
 	
 	for (j=5; j<=10; j=j+0.5) {
 		if (j<10)
			cout << setw(4) << j << "|";
		else
 			cout << j << setw(4) << "|";
 			
 		for (i=5;i<=yrs;i=i+5) {
 			brackets = 1+(j/100);
 			power = pow(brackets, i);
 			net = invest*power;
 			cout << "\t" << net << setw(5);
 		}
 		cout << endl;
 	}
	cout << endl;
	
	return 0;	
}