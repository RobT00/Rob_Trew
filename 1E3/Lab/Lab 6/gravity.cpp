#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

double grav_F (double m1, double m2, double d);

int main() {
	double m1, m2, d, grav;
	cout << "Enter the masses, separted by a space (in kg): ";
	cin >> m1 >> m2;
	cout << "Enter the distnace in metres: ";
	cin >> d;
	cout << setprecision(5) << endl;
	
	grav = grav_F(m1, m2, d);
	
	cout << "The gravitational force is: " << grav << " Newtons\n";
	
	return 0;
}

double grav_F (double m1, double m2, double d) {
	const double G = 6.674e-11;	
	double grav;
	
	return (m1*m2*G)/(pow(d, 2));
}