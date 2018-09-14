#include <iostream>

using namespace std;

int main()
{
    int yrds, ft, IN, in ;
    double cm ;

    cout << "Enter the centimetre value: " ;
    cin >> cm ;
    cout << "You entered " << cm << " cm" << endl;
    //Conversions//
    yrds = (cm/2.54)/36 ;
    ft = (cm/2.54)/12 ;
    IN = (((cm/2.54)/36) - yrds)*36 ;
    in = (((cm/2.54)/12) - ft )*12 ;
    //
    cout << "That is: " << yrds << " yrds and " << IN << " in." << endl;
    cout << "Or: " << ft << " ft and " << in << " in." << endl;

    return 0;
}
