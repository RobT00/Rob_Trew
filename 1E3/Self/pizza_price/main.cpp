#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

int main()
{
    double d, r, c, a, v, pi ;

    cout << "Enter the pizza diameter: " ;
    cin >> d ;
    cout << "Enter the pizza price: " ;
    cin >> c ;

    // calculations //
    pi = 4*atan(1) ;
    r = d/2 ;
    a = pi*(r*r) ;
    v = (c/a)*100 ;
    //
    cout << "The area is: " << a << " sq.in." << endl ;
    cout << "The price per square inch is: " << v << " cent" << endl;

    return 0;
}
