#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int main()
{
    int yrds, ft, in ;
    double cm, tot_in ;

    cout << "Enter the centimetre value: " ;
    cin >> cm ;
    cout << "You entered " << cm << " cm" << endl;
    //Conversions//
    tot_in = cm/2.54 ;
    yrds = tot_in/12/3 ;
    ft = fmod((tot_in/12), 3) ;
    in = fmod((tot_in), 12) ;
    //
    cout << "That is: " << yrds << " yrds, " << ft << " ft and " << in << " in." << endl;

    return 0;
}
