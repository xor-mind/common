// DateTime handles date and time solutions
// using the mysql format: YYYY-MM-DD hh:mm:ss and
// int variables for year, month, day, hour, minute and second.
// 
// It can get the current local time.
// it can subtract two times giving a delta for use with a start time,
// and eventually a days and hours between two dates.
#pragma once

#include <string>
#include <iostream>

class DateTime 
{
public:
    DateTime();
    // takes in a "YYYY-MM-DD hh:mm:ss" and set's the object's corresponding data.
    DateTime(std::string datetime);
    DateTime(int year, int month, int day, int hour, int minute, int second);

    // set's the date time members to local time. 
    void GetLocalDateTime();

    // set object from a mysql date time we set fill our members
    void ParseDateTime(const std::string& datetime);
    void Set(int year, int month, int day, int hour, int minute, int second);

    // accessors
    int Year() const { return year; }
    int Month() const { return month; }
    int Day() const { return day; }

    int Hour() const { return hour; }
    int Minute() const { return minute; }
    int Second() const { return second; }

    void Year(int year) { this->year = year; }
    void Month(int month) { this->month = month; }
    void Day(int day) { this->day = day; }

    void Hour(int hour) { this->hour = hour; }
    void Minute(int minute) { this->minute = minute; }
    void Second(int second) { this->second = second; }

    DateTime operator=(const std::string& datetime);
    DateTime operator-(const DateTime& subtrahend) const;
    bool operator==(const DateTime & rhs) const;

private:
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int second;  
};

// basically a "viewer" in MVC. Displays our object in the console using text.
std::ostream& operator<<(std::ostream& os, const DateTime& dt);
