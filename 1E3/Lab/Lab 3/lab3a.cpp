#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	string name;
	double hours, otime, rate, tax, prsi, gross, uni, total_tax, net, credits, bonus_rate, deduct;
	char credit;
	
	cout << setfill ('-') << setw(67) << "-" << endl;
	cout << "Enter hours worked, Rate of pay and full name separated by a space: \n" ;
	cout << setfill ('-') << setw(67) << "-" << endl;
	cout << setfill(' ');
	cin >> hours >> rate;
	getline(cin, name);	
	
	
	gross = hours * rate;

		
	tax = gross * 0.2;
	prsi = gross * 0.025;
	uni = 3.5;
	total_tax = tax + prsi + uni;
	
	net = gross - total_tax;
	
	cout << setprecision(1) << std::fixed << endl;
	cout << "Name: " << name << endl;
	cout << "Hours: " << hours << endl;
	cout << setprecision(2);
	cout << "Hourly Rate: " << rate << endl;
	cout << "Gross wage: " << gross << endl;
	cout << "Tax @ 20%: " << tax << endl;
	cout << "PRSI @ 2.5%: " << prsi << endl;
	cout << "Unions Due: " << uni << endl;
	cout << "Gross Deductions: " << total_tax << endl;
	cout << setfill('-') << setw(30) << "-" << endl;
	cout << setfill(' ') << "Net Pay: " << net << endl;
	
	return 0;
}