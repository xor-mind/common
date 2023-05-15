#define BOOST_TEST_MODULE Date Time
#include <boost/test/included/unit_test.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE(IsLeapYearTest)
{
    // IsLeapYearTest runs through all years from 1800 to 2020.
    // IsLeapYear() checks each year and compares it's result against
    // a known table. 

    int leapYears[] = {
        1804, 1808, 1812, 1816, 1820, 1824, 1828, 1832, 1836, 1840, 1844, 1848,
        1852, 1856, 1860, 1864, 1868, 1872, 1876, 1880, 1884, 1888, 1892, 1896,
        1904, 1908, 1912, 1916, 1920, 1924, 1928, 1932, 1936, 1940, 1944, 1948,
        1952, 1956, 1960, 1964, 1968, 1972, 1976, 1980, 1984, 1988, 1992, 1996,
        2000, 2004, 2008, 2012, 2016, 2020
    };

    for (int i = 1804; i < 2021; ++i)
    {
        using namespace std;

        bool myLearYearResult = 

        if (find(begin(leapYears), end(leapYears), i) != end(leapYears))
        {

        }
    }
}