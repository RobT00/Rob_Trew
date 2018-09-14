#include <iostream>
using namespace std;

int month_length (int m, int y);
int month_lengthd (int daynum);
int year_length (int y);
bool leap_year (int year);
int daynumber (int day, int month, int year);
void dayMthYr (int daynum, int& day, int& month, int& year);
//add here the declaration of the calc_date function for task 2

int main ()
{
    int day, month, year;
    day = 0;
    month = 0;
    year = 0;
    int number,d,m,y;
    cout << "Enter a date to be converted to a daynumber:";
    cin >> d >> m >> y;
    number = daynumber (d,m,y);
    cout << number << endl;
    dayMthYr ( number, day, month, year);
    //Write code here to test dayMthYr by converting a date to daynumber
    //and then using dyMthYr to convert it back, and checking if the
    // resulting day, month and year are what you started with; but be careful
    //not to let dayMthYr overwrite the values provided by the user.



    //Write code here to test the calc_date function


    return 0;
}


void dayMthYr (int daynum, int& day, int& month, int& year)
{   int leapdays;
    year = 0;
    month = 0;
    leapdays = daynum/1460;
    while(daynum>=365)
    {
        daynum = daynum - 365;
        year++;
    }
    daynum = daynum - leapdays;
    while(daynum>=31)
    {
        daynum = daynum - month_lengthd (daynum);
        month++;
    }
    year = year + 1900;
    month = month+1;
    day = daynum;
    cout<<"The coresponding date for that datenumber is "<<day<<" "<<month<<" "<<year;
}

int month_lengthd (int daynum)
{
    if(daynum>334)
        return 31;
    if(daynum>304)
        return 30;
    if(daynum>273)
        return 31;
    if(daynum>243)
        return 30;
    if(daynum>212)
        return 31;
    if(daynum>181)
        return 31;
    if(daynum>151)
        return 30;
    if(daynum>120)
        return 31;
    if(daynum>90)
        return 30;
    if(daynum>59)
        return 31;
    if(daynum>31)
        return 28;
    if(daynum>0)
        return 31;
}



int daynumber (int day, int month, int year){
    int y, m, daynumber;
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


//gives back the number of days in the given month of the given year
int month_length (int m, int y)
{
    if (m==2)
        if (leap_year(y))
	     return 29;
        else
		return 28;

    else if (m==9 || m==4 || m==6 || m==11)  //i.e. September, April, June, or November
        return 30;

    else
        return 31;
}


int year_length (int y)
{
    if (leap_year (y))
        return 366;

    else
        return 365;
}


bool leap_year (int year)
{
    //returns true if year is a leap year

    if (year % 4 == 0) //all others are definitely not leap
        if (year < 1583)
            return true;

        else //after 1583
            if ((year % 100 == 0) && (year % 400 != 0))   //e.g. 1900
                return false;
            else //e.g. 1904 or 2000
                return true;

        else //not divisible by 4
            return false;
}

