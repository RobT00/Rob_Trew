#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main () {
	double temp, max_temp, min_temp, avg_temp, prev_temp;
	string station_name;
    ifstream data;
    data.open ("data.txt");

	max_temp = min_temp = avg_temp = prev_temp = 0;

	while (station_name != "XXX") {
	data >> station_name;
		if (station_name == "XXX") {
			cout << "\n- END -" << endl;
			break;
			}

	if ((station_name != "XXX") or (station_name != "-999")){
		temp = 0;

		while (temp != -999) {
			data >> temp;

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
			if (temp == -999) {
				cout << std::fixed << setprecision(1) << endl;
				cout << "Station Name: " << station_name << endl;
				cout << "Maximum temperature: " << max_temp << endl;
				cout << "Minimum temperature: " << min_temp << endl;
				cout << setprecision(2) << "Average temperature: " << avg_temp << endl;
				max_temp = min_temp = avg_temp = prev_temp = 0;
				}
			}
		}
	}
	return 0;
}
