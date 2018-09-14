#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main () {
	double cost, rate_y, rate_m, repay, owe, interest, pay_interest, tot_interest;
	int count;
	
	cout << "Enter the cost: ";
	cin >> cost;
	cout << "Enter the monthly repayment: ";
	cin >> repay;
	cout << "Enter the yearly interest rate: ";
	cin >> rate_y;
	
	rate_m = (rate_y / 100) / 12;	
	owe = cost;
	tot_interest = 0;
	count = 0;
	
	while (owe > 0) {
		interest = owe * rate_m;
		tot_interest = tot_interest + interest; 
		pay_interest = repay - interest; 	
		owe = owe - pay_interest;
		count++;
	}
	
	cout << std::fixed << setprecision(2);
	cout << "The item will take: " << count << " months to repay" << endl;
	cout << "You will pay: " << tot_interest << " in interest" << endl;
	cout << "Giving the " << cost << " item a true value of: " << (cost + tot_interest) << endl;
	
	return 0;
}