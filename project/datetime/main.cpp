#include "../../include/DateTime.h"
#include <iostream>

using namespace std;

typedef unsigned int uint;

bool Divisible(uint a, uint b)
{
	return a % b == 0;
}

bool IsLeapYear(unsigned int year)
{
	// if year is divisible by 4 and not divisible 100
	// or if the year is divisible by 400, then it's a leap year.
	if (Divisible(year, 4) && !Divisible(year, 100) || Divisible(year, 400))
		return true;
	else
		return false;
}

int DaysInMonth(int month, int year)
{
	const int February = 2;

	if (month < 1 || month > 12)
	{
		cerr << "Error: month is out of range" << endl;
		return -1;
	}
	if (year < 0 )
	{
		cerr << "Error: year is less than zero" << endl;
		return -1;
	}

	// April, June, September, and November have 30 days 
	// January, March, May, July, August, October, and December have 31 days
	// feb has 28 or 29 depending on a leap year

	// let's first take care of February. 
	if (month == February)
		return IsLeapYear(year) ? 29 : 28;

	return 0;
}

int main()
{
	cout << IsLeapYear(1900) << endl;

	//cout << DaysInMonth(2, 2001) << endl;

	//DateTime currTime, prevTime;
	//currTime.GetLocalDateTime();
	//prevTime.Set("2023-05-11 12:0:0");

	//cout << currTime << endl << prevTime << endl;
	//cout << currTime - prevTime << endl;
}