#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    int i, n, f, s, print, num;

    i = 99999999999999999;
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
        if (print >= 0)
        {
            cout << print << endl;
            num = num++;
        }
        else if (print < 0)
            {
                cout << "\n\n";
                cout << "Buffer overflow occurred after " << num << " terms";
                break;
            }
    }
    cout << endl;
    return 0;
}
