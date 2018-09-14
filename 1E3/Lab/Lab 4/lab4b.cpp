#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	string name;
	double temp, max_temp, min_temp, avg_temp, sum;
	int count;
	cout << "Enter Station Name.\n";
	getline(cin, name);
	cout << "Enter temperature values separated by a space and ending in -999: \n";
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
		cout << std::fixed << setprecision(2) << endl;
		cout << "Station Name: " << name << endl;
		cout << "Maximum Tempurature: " << max_temp << endl;
		cout << "Minimum Tempurature: " << min_temp << endl;
		cout << "Average Tempurature: " << avg_temp << endl;

	return 0;
}