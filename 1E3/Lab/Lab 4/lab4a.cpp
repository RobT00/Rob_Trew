#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
	double payback, owe = 1500, rate_m = 0.01, pay = 50, true_pay, interest, tot_interest;
	int months;
	months = 0;
	payback = owe;
	tot_interest = 0;	
	while (payback > 0) {
		true_pay = pay - (payback * rate_m);
		interest = payback * rate_m;
		tot_interest = tot_interest + interest; 
		payback = payback - true_pay;
		months++;
		cout << std::fixed << setprecision(2);
		//cout << "Months" << setw(10) << "Paid Per Month" << setw(10) << "Total Interest \n";
		cout << months << " " << true_pay << " " << payback << " " << tot_interest << endl;
	}
	cout << "It took: " << months << " months to pay back the item" << endl;
	
	return 0;
}