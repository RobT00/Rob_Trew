#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    cout << std::fixed << setprecision(2);

    double rate, invest, pay, brackets, power, j, k, step;
    int yrs, interval, i;

    cout << "How much did you invest? ";
    cin >> invest;

    cout << "What interest rate would you like to see up to? ";
    cin >> rate;
    cout << "What would you like the step in interest rates to be? ";
    cin >> step;

    cout << "How many years would you like to see? ";
    cin >> yrs;

    cout << "What interval would you like to see? ";
    cin >> interval;

    cout << endl;

    cout << "Rate" << setw(5) << " | ";
    for (i = interval; i <= yrs; i = i + interval)
    {
        cout << setw(9) << i << " Years";
    }
    cout << endl;

    for (i = 1; i <= 103; i++)
        cout << "-";
    cout << endl;

    for (j = 1; j <= rate; j = j + step)
    {
        if (j < 10)
            cout << j << setw(5) << " | ";
        else cout << j << setw(4) << " | ";

        for (k = interval; k <= yrs; k = k + interval)
        {
            brackets = 1 + j/100;
            power = pow(brackets, k);
            pay = invest * power;
            cout << "\t" << pay << "\t";
        }
        cout << endl;
    }
    return 0;
}
