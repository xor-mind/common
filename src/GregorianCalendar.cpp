#include "GregorianCalendar.h"
#include <iostream>

using namespace std;

typedef unsigned int uint;

// ad_todo: this should be in a math interface.
bool Divisible(uint a, uint b)
{
	return a % b == 0;
}

bool GregorianCalendar::IsLeapYear(int year)
{
	if (year < 0)
	{
		cerr << "IsLeapYear() error: year is less than zero" << endl;
		return false;
	}

	// if year is divisible by 4 and not divisible 100
	// or if the year is divisible by 400, then it's a leap year.
	if (Divisible(year, 4) && !Divisible(year, 100) || Divisible(year, 400))
		return true;
	else
		return false;
}

int GregorianCalendar::DaysInMonth(int month, int year)
{
	const int February = 2;

	if (month < 1 || month > 12)
	{
		cerr << "DaysInMonth() error: month is out of range" << endl;
		return -1;
	}
	if (year < 0)
	{
		cerr << "DaysInMonth() error: year is less than zero" << endl;
		return -1;
	}

	// [April, June, September, November] have 30 days 
	// [January, March, May, July, August, October, December] have 31 days
	// feb has 28 or 29 days depending on leap year state.

	// let's first take care of February. 
	if (month == February)
		return IsLeapYear(year) ? 29 : 28;

	return 0;
}