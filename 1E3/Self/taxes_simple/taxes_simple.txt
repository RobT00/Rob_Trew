#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    string name;
    double hours, rate, gross, tax, prsi, union_dues, net;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter hours worked: ";
    cin >> hours;
    cout << "Enter rate of pay: ";
    cin >> rate;

    gross = hours * rate;
    tax = gross * 0.2;
    prsi = gross * 0.025;
    union_dues = 3.50;
    net = gross - (tax + prsi + union_dues);

    cout << endl;
    cout << "Name: " << setw(25) << name << endl;
    cout << "Hours: " << setw(25) << hours << endl;
    cout << "Hourly rate: " << setw(25) << rate << endl;
    cout << "Gross Wage: " << setw(25) << gross << endl;
    cout << "Tax @20%: " << setw(25) << tax << endl;
    cout << "PRSI @2.5%: " << setw(25) << prsi << endl;
    cout << "Union Dues: " << setw(25) << union_dues << endl;
    cout<< setfill('-') << setw(47) << "-" << endl;
    cout << setfill(' ') << "Net Pay: " << setw(25) << setprecision(5) << net << endl;

    return 0;
}
