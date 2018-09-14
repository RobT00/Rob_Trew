#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
bool prime (int i);
bool isAFactor(int i, int n);

int main() {
	int i, n, sum =1;
	i=2;
	for (i=2; i<1000; i++){
		if (prime (i))
			{cout << setw(5) << i;
			if (sum%10 == 0) {
				cout << endl;
			}
			sum++;
		}
		else 
			cout << std::fixed;
	}
	sum--;
	cout << "\nThere are " << sum << " primes up to 1000" << endl;
	return 0;	
}

bool isAFactor (int i, int n) {
	return(i%n == 0);
}

bool prime (int i) {
	int n;
	for(n=2; n<i; n++){
		if (isAFactor(i,n))
			return false;
	}
	return true;
}