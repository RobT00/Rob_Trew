#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

double Grav_F(double m1, double m2, double r);

int main()
{
    //const double G = 6.674e-11;
    double m1, m2, r, Force;
    cout << "Enter the first mass in kg: ";
    cin >> m1;
    cout << "Enter the second mass in kg: ";
    cin >> m2;
    cout << "Enter the distance between the masses (in metres): ";
    cin >> r;

    Force = Grav_F(m1, m2, r);
    cout << setprecision(8) << endl;
    cout << "The gravitational force is " << Force << " Newtons" << endl;
    return 0;
}
double Grav_F(double m1, double m2, double r)
{
    const double G = 6.674e-11;
    double F;
    r = pow(r, 2);
    F = (G*m1*m2)/r;

    return F;
}
