#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	string name;
	double temp, max_temp, min_temp, avg_temp, sum;
	int count;
	//cout << "Enter Station Name.\n";
	cin >> name;
	//cout << "Enter temperature values separated by a space and ending in -999: \n";
	while (name != "XXX") {
		cin >> temp;
	
		sum = count = 0;
		max_temp = min_temp = avg_temp = temp;
		while (temp != -999) {
			if (max_temp < temp)
			max_temp = temp;
		
			if (min_temp > temp)
			min_temp = temp;
		
			sum = temp + sum;
			count++;
			avg_temp = sum / count;
			cout << " ";
			cin >> temp;
		}
	//	cout << "**Invalid input**" << endl;
			cout << std::fixed << setprecision(2) << endl;
			cout << setw(20) << "Max" << setw(10) << "Min" << setw(10) << "Average" << endl;
			cout << name;
			cout << setw(10) <<  max_temp;
			cout << setw(10) << min_temp;
			cout << setw(10) << avg_temp << endl;
			cin >> name;
	}
	return 0;
}