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

int main ()
{
    int daynum, daynumber, process, d, m, y;

    cout << "Would like to convert [1]From day-number or [2]To day-number: ";
    cin >> process;

    while (process != 1 || process != 2)
    {
        if (process == 1)
        {
            cout << "Enter the day-number: ";
            cin >> daynumber;
            cout << std::fixed << setprecision(0) << endl;
            dayMthYr(daynumber, d, m, y);
            cout << d << " / " << m << " / " << y << endl;
            cout << endl;
            cout << "To double check, the date: ";
            cout << d << " / " << m << " / " << y << endl;
            daynum = number(d, m, y);
            cout << "Corresponds to the day-number: " << daynum << endl;;
            break;
        }

        else if (process == 2)
        {
            int daynum = 0;
            cout << "Enter the day, month and year (separated by a space): ";
            cin >> d >> m >> y;
            cout << std::fixed << setprecision(0) << endl;
            daynum = number(d, m, y);
            cout << daynum << endl;
            cout << endl;
            cout << "To double check, the day-number: " << daynum << endl;
            dayMthYr(daynum, d, m, y);
            cout << "Corresponds to the date: ";
            cout << d << " / " << m << " / " << y << endl;
            break;
        }

        else
            cout << "Please enter a valid input: ";

        cin >> process;
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
    //accumelate days in all years before the given one
    daynumber = 0;
    for (y = 1900; y < year; y++)
    {
        daynumber = daynumber + year_length (y);
    }
    //in the given year, accumelate days in all months before the given month
    for (m = 1; m < month; m++)
    {
        daynumber = daynumber + month_length(m, year);
    }
    //accumelate all the days in the given month, including the given day
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
