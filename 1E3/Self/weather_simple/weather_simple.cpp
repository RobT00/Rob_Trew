#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main () {
	double temp, max_temp, min_temp, avg_temp, prev_temp;
	string station_name;

	max_temp = min_temp = avg_temp = prev_temp = 0;

	cout << "Enter the station name: ";
	cin >> station_name;

	while (temp != -999) {
	cout << "Enter the temperature value: ";
	temp = 0;
	cin >> temp;

		if ((temp != -999) and (temp != 0)) {
			if (prev_temp == 0)
				min_temp = temp;
			else if ((temp <= prev_temp) and (temp <= min_temp))
				min_temp = temp;

			if (prev_temp == 0)
				max_temp = temp;
			else if ((temp >= prev_temp) and (temp >= max_temp))
				max_temp = temp;

			avg_temp =  (max_temp + min_temp) / 2;

			prev_temp = temp;

		}
	}
	cout << std::fixed << setprecision(1) << endl;
	cout << "Station Name: " << station_name << endl;
	cout << "Maximum temperature: " << max_temp << endl;
	cout << "Minimum temperature: " << min_temp << endl;
	cout << setprecision(2) << "Average temperature: " << avg_temp << endl;

	return 0;
}
