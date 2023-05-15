// DateTime is using the winapi for timer stuff, such as 
// GetLocalTime(SYSTEMTIME)  
#include "DateTime.h"

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

// from a mysql date time we set fill our members
void DateTime::Set(std::string datetime)
{
    ParseDateTime(datetime);
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

// returns local datetime in YYYY-MM-DD hh:mm:ss string
//std::string DateTime::GetCurrentDateTime()
//{
//    SYSTEMTIME st = { 0 };
//    GetLocalTime(&st);
//
//    stringstream sstm;

    // the formatting with setfill and setw makes it so the date and time always
    // has the same length of characters. A date like january will come out
    // as 1, and we want it to be 01. This wa
    // y I very easily retrieve the individual
    // tokens from a date & time string.
//    sstm << st.wYear << "-" << st.wMonth << "-" << st.wDay << " "
//        << st.wHour << ":" << st.wMinute << ":" << st.wSecond;
//    return sstm.str();
//}

DateTime DateTime::TimeDelta(const DateTime& subtrahend)
{
    //DateTime deltaTime(this);

    // The algorithm for the time delta comes from the following table:
    //   x1 year y1 month z1 day r1 hour s1 minute t1 seconds
    // - x2 year y2 month z2 day r2 hour s2 minute t2 seconds
    //
    // x1 and x2 are current and previous time respectively. same goes for all variables.
    // 
    // This is basically a subtraction table and the concept of "borrowing" 
    // is our solution when the bottom row's index is greater than the corresponding 
    // top row's index. 
    //
    // borrowing means to subtract a unit from the previous index, and add
    // it's equivalent value to the current index so that subtraction will remain
    // positive. This keeps our number format in it's usual positive structure
    // as opposited to a number whose structure allow negative parts.
    //
    // the only assumption is that the top number is greater than the bottom number.
    // this assumption will be asserted during processing.
    //
    
    // check to see if we need to borrow
    //     current second
    //   - previous second
    // ---------------------
    //if (subtrahend.Second() > this->Second())
    //{
    //    currTime.wMinute -= 1;
    //    currTime.wSecond += 60;
    //}

    //// check the minutes
    //if (prevTime.wMinute > currTime.wMinute)
    //{
    //    currTime.wHour -= 1;
    //    currTime.wMinute += 60;
    //}

    //// check the hours
    //if (prevTime.wMinute > currTime.wSecond)
    //{
    //    currTime.wHour -= 1;
    //    currTime.wMinute += 60;
    //}

    //delta.wYear = current.wYear - given.wYear;
    //delta.wMonth = current.wMonth - given.wMonth;
    //delta.wDay = current.wDay - given.wDay;
    //delta.wHour = current.wHour - given.wHour;
    //delta.wMinute = current.wMinute - given.wMinute;
    //delta.wSecond = current.wSecond - given.wSecond;

    DateTime dt; 
    return dt;
}

// This is like the Viewer in a MVC
std::ostream& operator<<(std::ostream& os, const DateTime& dt)
{
    os << dt.Year()  << "-" << dt.Month() << "-" << dt.Day() << " "
        << dt.Hour() << ":" << dt.Minute() << ":" << dt.Second();
    return os;
}

DateTime DateTime::operator-(const DateTime& subtrahend) const
{
    DateTime minuend(*this);

    // check to see if we need to borrow
    //        minuend: year .. minute second
    //   - subtrahend: year .. minute second
    // ---------------------
    if (subtrahend.second > minuend.second)
    {
        minuend.minute -= 1;
        minuend.second += 60;
    }

    if (subtrahend.minute > minuend.minute)
    {
        minuend.hour -= 1;
        minuend.minute += 60;
    }

    if (subtrahend.hour > minuend.hour)
    {
        minuend.day -= 1;
        minuend.hour += 24;
    }

    if (subtrahend.day > minuend.day)
    {
        //?
    }

    if (subtrahend.month > minuend.month)
    {
        minuend.year -= 1;
        minuend.month += 12;
    }

    if (subtrahend.year > minuend.year)
    {
        // shit lol :D
    }

    return minuend;
}


// misc notes/code
//a format i like
//sstm << st.wYear << "_" << setfill('0') << setw(2) << st.wMonth << "_" << setfill('0')
//<< setw(2) << st.wDay << " " << setfill('0') << setw(2) << st.wHour << setfill('0')
//<< setw(2) << st.wMinute;
//return sstm.str();