#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    string name;
    char tax_credit;
    double hours, extra_hours, rate, gross, tax, prsi, union_dues, net, bonus_rate, tax_credits, total_tax;
    int base_hours;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter hours worked: ";
    cin >> hours;
    cout << "Enter rate of pay: ";
    cin >> rate;

    if (hours > 35) {
        cout << "What is the overtime multiplier? " ;
        cin >> bonus_rate;
    }

    cout << "Do you have a tax credit? [Y/N] ";
    cin >> tax_credit;

    if ((tax_credit == 'Y') || (tax_credit == 'y')) {
        cout << "How much is your tax credit? ";
        cin >> tax_credits;
    }

    if (hours > 35) {
        extra_hours = hours - 35;
        base_hours = 35;
        gross = (extra_hours * (bonus_rate * rate)) + (base_hours * rate) ;
    }
    else
        gross = hours * rate;

    tax = gross * 0.2;
    prsi = gross * 0.025;
    union_dues = 3.50;

    if ((tax_credit == 'Y') || (tax_credit == 'y')) {
        total_tax = (tax + prsi + union_dues) - tax_credits;
        if (total_tax <= 0)
            total_tax = 0;
    }
    else {
        tax_credits = 0;
        total_tax = (tax + prsi + union_dues);
    }

    net = gross - (total_tax);

    cout << setprecision(2) << std::fixed << endl;

    cout << "Name: " << setw(20) << name << endl;

    if (hours > 35) {
        cout << "Normal hours: " << setw(20) << base_hours << endl;
        cout << "Overtime hours: " << setw(20) << extra_hours << endl;
    }

    else
        cout << "Hours: " << setw(20) << hours << endl;

    cout << "Hourly rate: " << setw(20) << rate << endl;

    if (hours > 35)
        cout << "Overtime rate: " << setw(20) << bonus_rate << endl;

    cout << "Gross Wage: " << setw(20) << gross << endl;
    cout << "Tax @20%: " << setw(20) << tax << endl;
    cout << "PRSI @2.5%: " << setw(20) << prsi << endl;
    cout << "Union Dues: " << setw(20) << union_dues << endl;

    if ((tax_credit = 'Y') ||(tax_credit = 'y'))
        cout << "Less Tax Credits: " << setw(20) << tax_credits << endl;

    cout << setfill('-') << setw(47) << "-" << endl;
    cout << setfill(' ') << "Net Pay: " << setw(20) << net << endl;

    return 0;
}
