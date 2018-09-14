#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>

using namespace std;

int main () {
	double temp, max_temp, min_temp, avg_temp, prev_temp;
	string place_name;

	ifstream ("data.txt");

	max_temp = min_temp = avg_temp = prev_temp = 0;

	cin >> place_name;
	while (place_name != "XXX")  {
		cin >> temp;
			while (temp != -999) {

				if ((temp < prev_temp) || (prev_temp == 0))
					min_temp = temp;

				if (temp > prev_temp)
					max_temp = temp;

				avg_temp =  (max_temp + min_temp) / 2;
				prev_temp = temp;
			}
			cin >> place_name;

    cout << std::fixed << setprecision(1) << endl;
	cout << "Place Name: " << place_name << endl;
	cout << "Maximum temperature: " << max_temp << endl;
	cout << "Minimum temperature: " << min_temp << endl;
	cout << "Average temperature: " << avg_temp << endl;

	cout << endl;
	}
	return 0;
}
