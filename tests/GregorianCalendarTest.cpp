#define BOOST_TEST_MODULE GregorianCalendarTest
#include <boost/test/included/unit_test.hpp>
#include <algorithm>

#include "../include/GregorianCalendar.h"

BOOST_AUTO_TEST_SUITE(TestGregorianCalendar)

// bool GregorianCalendar::IsLeapYear(int year)
// this tests all years form 1804 to 2020. if it's a leap year based on our table,
// we must assert GregorianCalendar::IsLeapYear().
BOOST_AUTO_TEST_CASE(TestIsLeapYear)
{
    int leapYears[] = {
        1804, 1808, 1812, 1816, 1820, 1824, 1828, 1832, 1836, 1840, 1844, 1848,
        1852, 1856, 1860, 1864, 1868, 1872, 1876, 1880, 1884, 1888, 1892, 1896,
        1904, 1908, 1912, 1916, 1920, 1924, 1928, 1932, 1936, 1940, 1944, 1948,
        1952, 1956, 1960, 1964, 1968, 1972, 1976, 1980, 1984, 1988, 1992, 1996,
        2000, 2004, 2008, 2012, 2016, 2020
    };

    GregorianCalendar gc; 

    for (int year = 1804; year < 2021; ++year)
    {
        using namespace std;

        // searching our table for year. 
        if (find(begin(leapYears), end(leapYears), year) != end(leapYears))
        {
            // if found. make sure my GregorianCalendar IsLeapYear function also sees 
            // the year as a leap year.
            BOOST_REQUIRE(gc.IsLeapYear(year));
        }
        else
            BOOST_REQUIRE(gc.IsLeapYear(year) == false);
    }
}

// int GregorianCalendar::DaysInMonth(int month, year)
// test
BOOST_AUTO_TEST_CASE(TestDaysInMonth)
{
    // days in month for non leap year. If leap year, Feb is 29 days.
    int nonLeapYear[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    GregorianCalendar gc;

    for (int year = 1970; year < 2023; ++year)
    {
        using namespace std;

        for (int month = 1; month <= 12; month++)
        {
            int daysInMonth = gc.DaysInMonth(month, year);

            // handle february
            if (month == 2)
            {
                if (gc.IsLeapYear(year))
                {
                    BOOST_REQUIRE(daysInMonth == 29);
                }
                else
                    BOOST_REQUIRE(daysInMonth == 28);
            }
            else
                BOOST_REQUIRE(daysInMonth == nonLeapYear[month - 1]);
        }
    }
}

BOOST_AUTO_TEST_CASE(TestDaysInYear)
{
    int leapYears[] = {
        1804, 1808, 1812, 1816, 1820, 1824, 1828, 1832, 1836, 1840, 1844, 1848,
        1852, 1856, 1860, 1864, 1868, 1872, 1876, 1880, 1884, 1888, 1892, 1896,
        1904, 1908, 1912, 1916, 1920, 1924, 1928, 1932, 1936, 1940, 1944, 1948,
        1952, 1956, 1960, 1964, 1968, 1972, 1976, 1980, 1984, 1988, 1992, 1996,
        2000, 2004, 2008, 2012, 2016, 2020
    };

    GregorianCalendar gc;

    for (int year = 1804; year < 2021; ++year)
    {
        using namespace std;

        int daysInYear = gc.DaysInYear(year);

        // searching our table for year. 
        if (find(begin(leapYears), end(leapYears), year) != end(leapYears))
        {
            // if found. make sure my GregorianCalendar IsLeapYear function also sees 
            // the year as a leap year.
            BOOST_REQUIRE(daysInYear == 366);
        }
        else
            BOOST_REQUIRE(daysInYear == 365);
    }
}

BOOST_AUTO_TEST_SUITE_END()