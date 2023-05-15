// DateTime handles date and time solutions
// in the mysql format: YYYY-MM-DD hh:mm:ss
// 
// It can get the current time.
// it can subtract two times

// what do i do with 
// bool IsLeapYear(unsigned int year) and
// int DaysInMonth(int month, int year)
// where does this belong
#pragma once

#include <string>
#include <iostream>

class DateTime 
{
public:
    DateTime();
    // takes in a "YYYY-MM-DD hh:mm:ss" and set's the object's corresponding data.
    DateTime(std::string datetime);

    // set's the date time members to local time. 
    void GetLocalDateTime();

    // set object from a mysql date time we set fill our members
    void Set(std::string datetime);
    // set object from date PODs
    void Set(int year, int month, int day, int hour, int minute, int second);

    //// returns local datetime in YYYY-MM-DD hh:mm:ss string
    //std::string GetCurrentDateTime();

    // a - b = c, 'a' is our datetime object and subtrahend is 'b'.
    DateTime TimeDelta(const DateTime& subtrahend);

    // accessors
    int Year() const { return year; }
    int Month() const { return month; }
    int Day() const { return day; }

    int Hour() const { return hour; }
    // This function promises not to modify the object
    int Minute() const { return minute; }
    int Second() const { return second; }

    void Year(int year) { this->year = year; }
    void Month(int month) { this->month = month; }
    void Day(int day) { this->day = day; }

    void Hour(int hour) { this->hour = hour; }
    void Minute(int minute) { this->minute = minute; }
    void Second(int second) { this->second = second; }

    //// This function promises not to modify the object
    DateTime operator-(const DateTime& subtrahend) const;

private:
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int second;

    void ParseDateTime(const std::string& datetime);
};

// basically a "viewer" in MVC
std::ostream& operator<<(std::ostream& os, const DateTime& dt);
//DateTime operator-(const DateTime& minuend, const DateTime& subtrahend);