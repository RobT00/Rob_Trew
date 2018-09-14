#include <iostream>
#include <string>

using namespace std;

int main()
{
    int feet, inches, num, inches_clean, feet_clean ;
    double cm, x, y ;
    string metric, imperial ;
    x = metric ;
    y = imperial ;

    cout << "Would you like to convert to (1)metric or (2)imperial?\n" ;
    cin >> var ;

    if ( x ) {
    cout << "Enter the number of centimetres: " ;
    cin >> cm ;
    cout << "You entered " << cm << "cm\n" ;
    cout << "In feet and inches that is: " ;
    //conversion into feet and inches//
    feet = ((cm/2.54)/12) ;
    inches = ((((cm/2.54)/12) - feet)*12) ;
    //
    cout << feet << "ft and " << inches << "in."  ;
    }
    else {
    cout << "Enter the number of feet: " ;
    cin >> feet ;
    cout << "Enter the number of inches: " ;
    cin >> inches ;
    cout << "You entered " << feet << "ft " << inches << "in.\n" ;
    cout << "In centimetres that is: " ;
    cout << ((feet*12)+inches)*2.54 << "cm\n" ;
    }
    return 0;
}
