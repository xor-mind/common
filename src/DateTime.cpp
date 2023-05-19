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
    year = stoi(token);

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

std::ostream& operator<<(std::ostream& os, const DateTime& dt)
{
    os << dt.Year()  << "-" << dt.Month() << "-" << dt.Day() << " "
        << dt.Hour() << ":" << dt.Minute() << ":" << dt.Second();
    return os;
}

DateTime DateTime::operator-(const DateTime& subtrahend) const
{
    DateTime minuend(*this);
    GregorianCalendar gc;

    // this subtraction algorithm is based on the pen and paper row 
    // based subtraction procedure(algorithm) we learned in grade school 
    // for whole numbers where we use borrowing.

    // the only difference between integers and YYYY-MM-DD timestamps
    // is that the month's have different days based on a few simple rules(31, 30, 29 or 28 days).

    // so when it's time to borrow a month and convert it to days. 
    // we must look at how many days it would take to get from the previous month to the next 
    // month. it's that simple. maybe think about it if you want.

    // the only other caveat when running this procedure, just as in integer subtraction,
    // is that we won't immediately borrow if it makes an element(months in this case) zero. to 
    // get around this, we for the moment skip borrowing from months and we first borrow from
    // the years element, which will allow us to then borrow from months without zeroing out the months
    // element in the minuend row. 

    // here lies the procedure:

    //a = "2019-1-1 0:0:0";
    //b = "2018-1-2 0:0:0";
    //Dab = "0-11-30 0:0:0";
    if (subtrahend.day > minuend.day)
    {
        minuend.month--;
        if (minuend.month == 0)
        {
            // the pen and paper algorithm requires us to continue borrowing at this point.
            // i.e. we're not allowed to make a number zero by borrowing. we must continue
            // to borrow up the chain.

            minuend.year--;
            if (subtrahend.year > minuend.year)
            {
                cerr << "trying to subtract from a date a date in the future!" << endl;
                minuend.Set(0, 0, 0, 0, 0, 0);
                return minuend;
            }

            minuend.month += 12;
        }
        int numberOfdays = gc.DaysInMonth(minuend.month, minuend.year);
        minuend.day += numberOfdays;
    }

    if (subtrahend.month > minuend.month)
    {
        minuend.year -= 1;
        minuend.month += 12;
    }

    if (subtrahend.year > minuend.year)
    {
        cerr << "trying to subtract from a date a date in the future!" << endl;
        minuend.Set(0, 0, 0, 0, 0, 0);
        return minuend;
    }

    minuend.day   -= subtrahend.day;
    minuend.month -= subtrahend.month;
    minuend.year  -= subtrahend.year;

    return minuend;
}

bool DateTime::operator==(const DateTime & rhs) const
{
    return    second == rhs.second && minute == rhs.minute && hour == rhs.hour
           && day == rhs.day && month == rhs.month && year == rhs.year;
}

DateTime DateTime::operator=(const string& datetime)
{
    ParseDateTime(datetime);
    return *this;
}


// misc notes/code
//a format i like
//sstm << st.wYear << "_" << setfill('0') << setw(2) << st.wMonth << "_" << setfill('0')
//<< setw(2) << st.wDay << " " << setfill('0') << setw(2) << st.wHour << setfill('0')
//<< setw(2) << st.wMinute;
//return sstm.str();


//DateTime DateTime::TimeDelta(const DateTime& subtrahend)
//{
//    //DateTime deltaTime(this);
//
//    // The algorithm for the time delta comes from the following table:
//    //   x1 year y1 month z1 day r1 hour s1 minute t1 seconds
//    // - x2 year y2 month z2 day r2 hour s2 minute t2 seconds
//    //
//    // x1 and x2 are current and previous time respectively. same goes for all variables.
//    // 
//    // This is basically a subtraction table and the concept of "borrowing" 
//    // is our solution when the bottom row's index is greater than the corresponding 
//    // top row's index. 
//    //
//    // borrowing means to subtract a unit from the previous index, and add
//    // it's equivalent value to the current index so that subtraction will remain
//    // positive. This keeps our number format in it's usual positive structure
//    // as opposited to a number whose structure allow negative parts.
//    //
//    // the only assumption is that the top number is greater than the bottom number.
//    // this assumption will be asserted during processing.
//    //
//
//    // check to see if we need to borrow
//    //     current second
//    //   - previous second
//    // ---------------------
//    //if (subtrahend.Second() > this->Second())
//    //{
//    //    currTime.wMinute -= 1;
//    //    currTime.wSecond += 60;
//    //}
//
//    //// check the minutes
//    //if (prevTime.wMinute > currTime.wMinute)
//    //{
//    //    currTime.wHour -= 1;
//    //    currTime.wMinute += 60;
//    //}
//
//    //// check the hours
//    //if (prevTime.wMinute > currTime.wSecond)
//    //{
//    //    currTime.wHour -= 1;
//    //    currTime.wMinute += 60;
//    //}
//
//    //delta.wYear = current.wYear - given.wYear;
//    //delta.wMonth = current.wMonth - given.wMonth;
//    //delta.wDay = current.wDay - given.wDay;
//    //delta.wHour = current.wHour - given.wHour;
//    //delta.wMinute = current.wMinute - given.wMinute;
//    //delta.wSecond = current.wSecond - given.wSecond;
//
//    DateTime dt;
//    return dt;
//}