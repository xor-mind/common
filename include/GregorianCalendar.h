#pragma once

// so far this just returns ints and a bool. nice!
class GregorianCalendar
{
public:
	bool IsLeapYear(int year);
	int DaysInMonth(int month, int year);
	int DaysInYear(int year);
};