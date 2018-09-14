#include <iostream>
#include <string>

int month_length (int m, int y);
int year_length (int y);
bool leap_year (int year);

using namespace std;

int main()
{
    int y, m, d, daynumber;
    daynumber = 23348;
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

    cout << d << " / " << m << " / " << y << endl;
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
