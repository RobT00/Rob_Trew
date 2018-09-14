#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    int i, n, f, s, print, num;

    cout << "Please enter a positive integer that would like to see up to: ";
    cin >> i;
    num = 0;
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
        if (print < i)
        {
            cout << print << endl;
            num = num++;
        }
        else
           {
            cout << "\n\n";
            cout << "Up to the integer " << i << " there are " << num << " terms";
            break;
           }
    }
    cout << endl;
    return 0;
}
