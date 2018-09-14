#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    int i, n, f, s, print;

    cout << "Please enter a positive integer, representing the number of terms you wish to see: ";
    cin >> i;

    f = 0;
    s = 1;
    for (n = 0; n < i; n++)
    {
        if (n <= 1)
            print = n;
        else
        {
            print = f + s;
            f = s;
            s = print;
        }
        cout << print << endl;
    }
    return 0;
}
