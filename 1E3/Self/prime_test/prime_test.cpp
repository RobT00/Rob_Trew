#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    int n, i, lim, sum = 1;
    cout << "Enter how far you would like to see primes up to: ";
    cin >> lim;
    cout << "The following numbers are primes up to " << lim << ": " << endl;
    for (n=2; n < lim; n++)
    {
        bool prime = true;

        for (i = 2; i < n; i++)
        {
            if (n%i == 0)
            {
                prime = false;
                break;
            }
        }
		if (prime)
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
