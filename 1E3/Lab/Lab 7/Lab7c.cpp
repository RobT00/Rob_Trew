//Functions for Pratical 7 - 2016

#include <iostream>
using namespace std;

int month_length (int m, int y);
int year_length (int y);
bool leap_year (int year);
int daynumber (int day, int month, int year);
void dayMthYr (int daynum, int& d, int& m, int& y);
int calc_date (int daynum, char change, int amount, char type);
//add here the declaration of the calc_date function for task 2

int main ()
{
    int daynum, d, m, y, amount;
    cout << "Enter day-number: ";
    cin >> daynum;
	
	dayMthYr(daynum, d, m, y);
	cout << "Original date: " << endl;
	cout << d << " / " << m << " / " << y << endl;
	
	char change, type;
	cout << "Enter the change :";
	cin >> change >> amount >> type;
	daynum = calc_date (daynum, change, amount, type);
	
	dayMthYr (daynum, d, m, y);
	
	cout << "That is: " << d << " / " << m << " / " << y << endl;
	cout << endl;
	daynum = daynumber(d, m, y);
	cout << "To double check, the daynumber is: " << daynum << endl;
	
    return 0;
}


void dayMthYr (int daynum, int& d, int& m, int& y)
{
   
	y = 1900;
    for (; daynum > 365; y++)
    	daynum = daynum - year_length (y);
    
    
    m = 1;
    for (; daynum > 31 ; m++)
    	 daynum = daynum - month_length(m, y);
    
    
    d = 1;
	for (; daynum >= 0 ; d++)
    {	
    	daynum = daynum - 1;
		if (daynum <= 0)
			break;
    }
 
}

//converts a date to a daynumber
int daynumber (int day, int month, int year)
{
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

int calc_date (int daynum, char change, int amount, char type)
{
	int d, m, y;
	
	if  (type == 'd') {
		if (change == '+')
			daynum = daynum + amount;
		else
			daynum = daynum - amount;
	}
	
	else if (type == 'w') {
		amount = amount * 7;
		if (change == '+')
			daynum = daynum + amount;
		else
			daynum = daynum - amount;
	}
	
	else if (type == 'y') {
		dayMthYr (daynum, d, m, y);
		if (change == '+')
			y = y + amount;
		else
			y = y - amount;
		
		daynum = daynumber (d, m, y);
		
	}
	return daynum;	
}

