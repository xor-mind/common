// DateTime is using the winapi for timer stuff, such as 
// GetLocalTime(SYSTEMTIME)  
#include "DateTime.h"
#include "GregorianCalendar.h"

#include <windows.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>

using namespace std;

DateTime::DateTime()
    : year(0), month(0), day(0),
      hour(0), minute(0), second(0)
{}

DateTime::DateTime(string datetime)
{
    ParseDateTime(datetime);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
:
    year(year),
    month(month),
    day(day),

    hour(hour),
    minute(minute),
    second(second)
{}

void DateTime::ParseDateTime(const string& datetime)
{
    // ad_todo: add error handling!

    istringstream ss(datetime);
    string token;

    // ad_style: I tried while loops but the below code feels cleaner.

    // Read year
    getline(ss, token, '-');
    // the year maybe negative
    bool negative = false;
    if (token == "")
    {
        negative = true;
        // read in that the integer
        getline(ss, token, '-');
    }

    year = stoi(token);
    if ( negative)
        year = -year;

    // Read month
    getline(ss, token, '-');
    month = stoi(token);

    // Read day
    getline(ss, token, ' ');
    day = stoi(token);

    // Read Hour
    getline(ss, token, ':');
    hour = stoi(token);

    // Read minute
    getline(ss, token, ':');
    minute = stoi(token);

    // Read second
    getline(ss, token);
    second = stoi(token);
}



// set's the date time members to local time. 
void DateTime::GetLocalDateTime()
{
    SYSTEMTIME st = { 0 };
    GetLocalTime(&st);
    Set(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
}

void DateTime::Set(int year, int month, int day, int hour, int minute, int second)
{
    Year(year);
    Month(month);
    Day(day);

    Hour(hour);
    Minute(minute);
    Second(second);
}

std::string DateTime::to_string() const
{
    std::ostringstream oss;
    oss << *this;

    return oss.str();
}

std::string DateTime::Date() const
{
    std::stringstream ss(to_string());
    std::string date;
    ss >> date;

    return date;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt)
{
    os << dt.Year()  << "-" << dt.Month() << "-" << dt.Day() << " "
        << dt.Hour() << ":" << dt.Minute() << ":" << dt.Second();
    return os;
}

// returns a TimeDelta. I need to make this officially part of the 
// interface/implementation. But this isn't a dateTime object. This is a delta.
// it's different. a date time object can be xxxx-12-31 23:59:59
// but a delta can never be that. because 12 months based on a delta
// + initial dateTime, is always goign to be xxxx+1-0-31 23:59:59.
// hopefully this explains some of the code below.
DateTime DateTime::operator-(const DateTime& subtrahend) const
{
    DateTime minuend(*this);
    GregorianCalendar gc;

    // this subtraction algorithm is based on the pen and paper row 
    // based subtraction procedure(algorithm) we learned in grade school 
    // for whole numbers where we use borrowing.

    // the only difference between integers and YYYY-MM-DD timestamps
    // is that the month's have different days based on a few simple rules(31, 30, 29 or 28 days).


    // here lies the procedure:
    if (subtrahend.second > minuend.second)
    {
        minuend.minute--;
        minuend.second += 60;
    }

    if (subtrahend.minute > minuend.minute)
    {
        minuend.hour--;
        minuend.minute += 60;
    }

    if (subtrahend.hour > minuend.hour)
    {
        minuend.day--;
        minuend.hour += 24;
    }

    if (subtrahend.day > minuend.day)
    {
        minuend.month--;
        // if the month is zero, it means we're borrowing from December, and we need
        // we need to figure out how many days from the previous month we would have to go through
        // to get to the current minuend's day.
        int month = (minuend.month == 0 ? 12 : minuend.month);
        int numberOfdays = gc.DaysInMonth(month, minuend.year);
        minuend.day += numberOfdays;
    }

    if (subtrahend.month > minuend.month)
    {
        minuend.year -= 1;
        minuend.month += 12;
    }

    // it's okay if it's negative
    //if (subtrahend.year > minuend.year)
    //{
    //    cerr << "trying to subtract from a date a date in the future!" << endl;
    //    minuend.Set(0, 0, 0, 0, 0, 0);
    //    return minuend;
    //}

    minuend.second -= subtrahend.second;
    minuend.minute -= subtrahend.minute;
    minuend.hour   -= subtrahend.hour;
    minuend.day    -= subtrahend.day;
    minuend.month  -= subtrahend.month;
    minuend.year   -= subtrahend.year;

    return minuend;
}

//// this is a date time...
// wait a minute, I"m drunk, and ++ doesn't mean anything. am incrementing hours, minutes, milliseconds? lol
// we'll do days simply to make it easier to increment throughout months in for loops. 
// this is pretty specific code though and is kinda abusing the what ++ means for a datetime.
// semantics abuse? 
DateTime DateTime::operator++(int)
{
    // we need to return a copy because the post-increment operator
    // only mutates the object after the object get's used in the current line of
    // of code, or something like that.
    DateTime dt(*this);

    // add one day
    DateTime b("0-0-1 0:0:0");
    *this = *this + b;


    return dt;
}

DateTime DateTime::operator+(const DateTime& addend) const
{
    // using a grade school table addition algorithm,
    // whichs uses the concept of a carry to handle overflow
    // (.e.g 59 second + 1 second = 1 minute 0 seconds)
    DateTime augend(*this), sum;
    GregorianCalendar gc;

    // the subtraction function, which is used to create the delta that the inverse subtraction function, i.e.
    // addition works upon, uses an initial point and end point(being date-times). 
    // i think of the initial time's day number as a positive integer that has completed that many days of a month. 
    // i.e. it doesn't matter how far away the IP and EP day positions are year/month wise.
    // it only matters that for that last EPs month/day, how close is IP day to EP day? at most the IP days will have to cross
    // into a new month.

    // were not seeing when the days cross at the beginning, but the end. this is why year/mont are added first. 
    // the days subtraction assume it's the next month.
    sum.year = augend.year + addend.year;
    // for now there's no overflow checks for year.

    // month time
    sum.month = augend.month + addend.month;
    if (sum.month > 12)
    {
        // just like days in a month, months start at 1, not zero.
        int remainder = sum.month % (12+1);
        sum.year++;
        sum.month = remainder + 1;
    }

    // here lies the procedure:
    sum.second = augend.second + addend.second;
    sum.minute = augend.minute + addend.minute;
    sum.hour   = augend.hour   + addend.hour;
    sum.day    = augend.day    + addend.day;


    // there are 6 cases to go through
    // (1) 
    
    if (sum.second >= 60)
    {
        // the sum's seconds column can't be larger than 59 seconds by the rules of the 
        // timestamp(HH:MM:SS). 
        // after adding the two time stamps, if the seconds column is greater than 59 seconds, 
        // we will carry over 60 seconds to to the minute column by adding one minute
        // (which equals 60 seconds) to the time stamp,
        // and the seconds remainder will be be left in the seconds column. We use the 
        // modulus operation to figure out that remainder.
        // .e.g 80 seconds(which > 59 seconds) -> 80 % 60 = 20. Add 1 minute, and now 
        // we have figured out that 80 seconds = 1 minute and 20 seconds. 
        int remainder = sum.second % 60; 
        sum.minute++;
        sum.second = remainder;
    }

    // (2)
    
    if (sum.minute >= 60)
    {
        // as before with the seconds we need to process the minute overflow.
        // the minutes column must be less than 60
        int remainder = sum.minute % 60;
        sum.hour++;
        sum.minute = remainder;
    }

    // (3)
    
    if (sum.hour >= 24)
    {
        // as before with the seconds and minutes columns, we need to process the hour overflow.
        // the hour column must be less than 24 hours
        int remainder = sum.hour % 24;
        sum.day++;
        sum.hour = remainder;
    }


    // followed next by days
    // 
    // ad_hack: i really need time deltas, and since I don't have
    // them yet, and I have no way of telling whether the parameters are
    // datetimes or not, the best I can do is see if the year is
    // at least zero... 
    if (sum.year != 0)
    {
        int numberOfdays = gc.DaysInMonth(sum.month, sum.year);

        if (sum.day > numberOfdays)
        {
            // as before with everything else, we now to need to process the days overflow.
            // the days must be less than the amount of days in that month + 1, because days
            // start at 1, not zero, unlike the HH:MM:SS portion of the time stamp.
            int remainder = sum.day % numberOfdays;
            sum.month++;
            sum.day = remainder; // normalize from [0, days - 1] to [

            // need to check year now
            if (sum.month > 12)
            {
                // just like days in a month, months start at 1, not zero.
                int remainder = sum.month % (12 + 1);
                sum.year++;
                sum.month = remainder + 1;
            }
        }
    }
    return sum;
}

bool DateTime::operator==(const DateTime & rhs) const
{
    return    second == rhs.second && minute == rhs.minute && hour == rhs.hour
           && day == rhs.day && month == rhs.month && year == rhs.year;
}

bool DateTime::operator<(const DateTime& rhs) const
{
    DateTime delta = rhs - *this;

    if (delta.Year() >= 0 && !delta.IsZero())
        return true;
    else
        return false;
}

DateTime DateTime::operator=(const string& datetime)
{
    ParseDateTime(datetime);
    return *this;
}

bool DateTime::IsZero() const
{
    return    second == 0 && minute == 0 && hour == 0
        && day == 0 && month == 0 && year == 0;
}

int DateTime::ToDays(const DateTime& initial)
{
    GregorianCalendar gc;

    int totalDays = 0;
    for (int i = 0; i < year; i++)
    {
        totalDays += gc.DaysInYear(initial.year + i);
    }

    for (int i = 0; i < month; i++)
    {
        totalDays += gc.DaysInMonth(initial.month + i, initial.year + year);
    }

    totalDays += day;

    return totalDays;
}

DateTime DateTime::Time() const
{
    DateTime time(*this);

    time.year = 0;
    time.month = 0;
    time.day = 0;

    return time;
}


// misc notes/code
//a format i like
//sstm << st.wYear << "_" << setfill('0') << setw(2) << st.wMonth << "_" << setfill('0')
//<< setw(2) << st.wDay << " " << setfill('0') << setw(2) << st.wHour << setfill('0')
//<< setw(2) << st.wMinute;
//return sstm.str();

