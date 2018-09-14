#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int month_length (int m, int y);
int year_length (int y);
bool leap_year (int year);
void dayMthYr (int daynumber, int& d, int& m, int& y);
int number (int day, int month, int year);
int calc_date (int daynumber, char change, int amount, char type);

int main ()
{
    int daynumber, amount, d, m, y;
    char change, type, answer;

    cout << "Please enter the starting day-number: ";
    cin >> daynumber;
    dayMthYr(daynumber, d, m, y);
    cout << daynumber << endl;
    cout << d << " / " << m << " / " << y << endl;
    cout << endl;
    cout << "Please enter the change from the date you would like: ";
    cin >> change >> amount >> type;

    daynumber = calc_date (daynumber, change, amount, type);
    cout << endl;
    cout << daynumber;
    dayMthYr(daynumber, d, m, y);
    cout << endl;
    cout << d << " / " << m << " / " << y << endl;

    cout << "Would you like to make any more changes? [Y]/[N] ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y')
        {
        cout << "Please enter '000' when you are finished making changes" << endl;
        cout << "Please enter the change from the date you would like: ";
        cin >> change >> amount >> type;
            while (change != '0' && amount != 0 && type != '0')
            {
                daynumber = number(d, m, y);

                daynumber = calc_date (daynumber, change, amount, type);
                cout << endl;
                cout << daynumber;
                dayMthYr(daynumber, d, m, y);
                cout << endl;
                cout << d << " / " << m << " / " << y << endl;
                cout << endl;
                cout << "Please enter the change from the date you would like: ";
                cin >> change >> amount >> type;
            }
        }
    return 0;
}

void dayMthYr (int daynumber, int& d, int& m, int& y)
{
    for (y = 1900; daynumber > 365; y++)
        {
        daynumber = daynumber - year_length(y);
        }
    for (m = 1; daynumber > 31; m++)
        {
        daynumber = daynumber - month_length(m, y);
        }
    for (d = 1; daynumber >= 0; d++)
        {
        daynumber = daynumber - 1;
        if (daynumber <= 0)
            break;
        }
}

int number (int day, int month, int year)
{
    int m, y, daynumber;

    daynumber = 0;
    for (y = 1900; y < year; y++)
    {
        daynumber = daynumber + year_length (y);
    }

    for (m = 1; m < month; m++)
    {
        daynumber = daynumber + month_length(m, year);
    }

    daynumber = daynumber + day;

    return daynumber;
}
int month_length (int m, int y)
{
    if (m==2)
        if (leap_year(y))
            return 29;
        else
            return 28;
    else if (m==9 || m==4 || m==6 || m==11)
        return 30;
    else
        return 31;
}

int year_length (int y)
{
    if (leap_year(y))
        return 366;
    else
        return 365;
}

bool leap_year (int year)
{
    if (year % 4 == 0)
        if (year < 1583)
            return true;
        else
            if ((year % 100 == 0) && (year % 400 != 0))
                return false;
            else
                return true;
        else
            return false;
}

int calc_date (int daynumber, char change, int amount, char type)
{
    if (type == 'd')
    {
        if (change == '+')
            daynumber = daynumber + amount;
        else if (change == '-')
            daynumber = daynumber - amount;

        return daynumber;
    }

    else if (type == 'w')
    {
        amount = amount * 7;
        if (change == '+')
            daynumber = daynumber + amount;

        else if (change == '-')
            daynumber = daynumber - amount;

        return daynumber;
    }

    else if (type == 'y')
    {
        int d, m, y;
        dayMthYr(daynumber, d, m, y);

        if (change == '+')
            y = y + amount;

        else if (change == '-')
            y = y - amount;

        daynumber = number(d, m, y);

        return daynumber;
    }
    return 0;
}
