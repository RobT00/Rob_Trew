#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int units;
	double rent, thresh, profit, cost, prev_profit;

	cout << "Enter the units rented: ";
	cin >> units;
	cout << "Enter the rent of a unit: ";
	cin >> rent;
	cout << "Enter the rent increase that results in a vacancy: ";
	cin >> thresh;
	cout << "Enter the maintenance cost per unit: ";
	cin >> cost;

	prev_profit = 0;
	profit = 1;

	cout << "\nRent\t" << "Units\t" << "Profit\t" << endl;

	while (profit > prev_profit) {
		prev_profit = profit;
		double gross = rent * units;
		double less = units * cost;
		profit = gross - less;
		if (profit < prev_profit)
			break;
		cout << rent << "\t";
		cout << units << "\t";
		cout << profit << "\t" << endl;
		units--;
		rent = rent + thresh;
	}
	return 0;
}