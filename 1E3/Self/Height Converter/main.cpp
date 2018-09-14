#include <iostream>

using namespace std;

int main()
{
    int feet, inches;
    cout << "Enter the number of feet: " ;
    cin >> feet ;
    cout << "Enter the number of inches: " ;
    cin >> inches ;
    cout << "You entered " << feet << "ft " << inches << "in.\n" ;
    cout << "In centimetres, that is: " ;
    cout << ((feet*12)+inches)*2.54 << "\n" ;

    return 0;
}
