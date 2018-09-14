#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

bool isAFactor(int i, int n);
bool prime(int n, int i);

int main()
{
    int n, i, lim, sum = 1;
    cout << "Enter how far you would like to see primes up to: ";
    cin >> lim;
    cout << "The following numbers are primes up to " << lim << ": " << endl;

   for (n=2; n < lim; n++)
    {   if(prime(n, i))
            cout << std::fixed;
        else
        {
            cout << setw(5) << left << n;
            if (sum%10 == 0)
                cout << endl;

            sum++;
        }
    }
    sum--;
    cout << "\n\nThere are " << sum << " primes up to " << lim << endl;
    return 0;
}

bool isAFactor(int i, int n)
{
    return (n%i == 0);
}

bool prime(int i, int n)
{
    for (i = 2; i < n; i++)
    {
        if(isAFactor(i, n))
            return false;
    }

    return true;
}
