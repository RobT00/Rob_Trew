#include <iostream>

using namespace std;

int main()
{
    int fahrenheit ;
    cout << "Enter the temperature value in Fahrenheit \n" ;
    cin >> fahrenheit ;
    cout << "You entered " << fahrenheit << " degrees fahrenheit\n" ;
    cout << "That is " ;
    cout << ((fahrenheit - 32) * 5/9 ) << " degrees centigrade" ;

    return 0;
}
