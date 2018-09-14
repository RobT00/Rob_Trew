#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void bill(const string num[], const string name[], string acc[], const double balance[], double r_mins[], double d_mins[], double e_mins[], const int j);
double cost(const string acc[], double r_mins[], double d_mins[], double e_mins[], int i);

const int SIZE = 100;
ifstream data;

int main()
{
    data.open ("H:\\Google Drive\\1E3\\Coding\\Lab\\Lab 8\\Phone_bill.txt");

    string num[SIZE], name[SIZE], acc[SIZE];
    double balance[SIZE], r_mins[SIZE], d_mins[SIZE], e_mins[SIZE];

    int i = 0;

    data >> num[i];
    while (num[i] != "X0000")
    {
//        cout << num[i];
        data >> name[i];
//        cout << "\t" << name[i];
        data >> balance[i];
//        cout << "\t" << balance[i];
        data >> acc[i];
//        cout << "\t" << acc[i];
        if (acc[i] == "R")
        {
            data >> r_mins[i];
//            cout << "\t" << r_mins[i];
        }
        else if (acc[i] == "P")
        {
            data >> d_mins[i];
//            cout << "\t" << d_mins[i];
            data >> e_mins[i];
//            cout << "\t" << e_mins[i];
        }
        i++;
//        cout << endl;
        data >> num[i];
    }
    bill(num, name, acc, balance, r_mins, d_mins, e_mins, i);
//    cout << "\nfin" << endl;
    data.close();
    return 0;
}

void bill(const string num[], const string name[], string acc[], const double balance[], double r_mins[], double d_mins[], double e_mins[], const int j)
{
    for (int i = 0; i < j; i++)
    {
        cout << setfill(' ');
        if (i > 0)
            cout << setfill('*') << setw(25) << "*" << endl;
        cout << "Account ID: " << num[i] << endl;
        cout << "Surname: " << name[i] << endl;
        if (acc[i] == "R")
            acc[i] = "Regular";
        else if (acc[i] == "P")
            acc[i] = "Premium";
        cout << "Account Type: " << acc[i] << endl;
        cout << "Previous Balance: EUR " << balance[i] << endl;
        double pay = cost(acc, r_mins, d_mins, e_mins, i);
        cout << "Total Bill this Month: EUR " << pay;
        cout << endl;
        cout << "TOTAL: EUR " << (pay+balance[i]) << endl;
    }
}

double cost(const string acc[], double r_mins[], double d_mins[], double e_mins[], int i)
{
    double pay = 0;//, time = 0;
    if (acc[i] == "Regular")
    {
        r_mins[i] = r_mins[i] - 50;
        //cout << r_mins[i] << endl;
        if (r_mins[i] > 0)
        {
            //time = r_mins[i] * 0.2;
            pay = pay + (r_mins[i] * 0.2);
        }
        pay = pay + 10;
    }
    else if (acc[i] == "Premium")
    {
        pay = 25;
        d_mins[i] = d_mins[i] - 75;
        e_mins[i] = e_mins[i] - 100;
        if (d_mins[i] > 0)
            pay = pay + (d_mins[i] * 0.1);
        if (e_mins[i] > 0)
            pay = pay + (e_mins[i] * 0.05);
    }
    cout << std::fixed << setprecision(2);
    return pay;
}
