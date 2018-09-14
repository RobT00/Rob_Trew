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
	
	if (hours > 35) {
		cout << "Enter overtime multiplier: ";
		cin >> bonus_rate;
	}
	
	cout << "Do you have a tax credit? [Y/N] ";
		cin >> credit;
	if ((credit == 'Y') || (credit == 'y')) {
		cout << "How much is your tax credit? ";
		cin >> credits;
	}
	
	if (hours > 35) {
		otime = hours - 35;
		hours = 35;
		gross = (otime * (bonus_rate * rate) + (hours * rate));
	}
	else 
		gross = hours * rate;
		
	tax = gross * 0.2;
	prsi = gross * 0.025;
	uni = 3.5;
	total_tax = tax + prsi + uni;
	
	deduct = total_tax - credits;
	if (deduct <= 0)
		deduct = 0;
	
	net = gross - deduct;
	
	cout << setprecision(1) << std::fixed << endl;
	cout << "Name: " << setw(20) << right << name << endl;
	cout << "Standard Hours: " << setw(20) << right << hours << endl;
	cout << "Overtime Hours: " << setw(20) << right << otime << endl;
	cout << setprecision(2);
	cout << "Hourly Rate: " << setw(20) << right << rate << endl;
	cout << "Overtime Rate: " << setw(20) << right << bonus_rate*rate << endl;
	cout << "Gross wage: " << setw(20) << right << gross << endl;
	cout << "Tax @ 20%: " << setw(20) << right << tax << endl;
	cout << "PRSI @ 2.5%: " << setw(20) << right << prsi << endl;
	cout << "Unions Due: " << setw(20) << right << uni << endl;
	cout << "Gross Deductions: " << setw(5) << right << total_tax << endl;
	cout << "Less Tax Credits: " << right << setw(5) << credits << endl;
	cout << setfill('-') << setw(30) << "-" << endl;
	cout << setfill(' ') << "Net Pay: " << right << setw(20) << net << endl;
	
	return 0;
}