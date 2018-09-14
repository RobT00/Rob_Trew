#include <iostream>

using namespace std;

int main()
{
    int in, ft, yrds ;
    double cm ;

    cout << "Enter the cm: " ;
    cin >> cm ;
    cout << "You entered: " << cm << " cm" << endl ;

    in = cm/2.54 ;
    yrds = in/36 ;
    in = in%36 ;
    ft = in/12 ;
    in = in%12 ;

    cout << "That is: " << yrds << " yrds, " << ft << " ft and " << in << " in." << endl ;
    return 0;
}
