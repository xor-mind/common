#define BOOST_TEST_MODULE DateTimeTest
#include <boost/test/included/unit_test.hpp>

#include "DateTime.h"

BOOST_AUTO_TEST_SUITE(TestDateTime)

BOOST_AUTO_TEST_CASE(TestToString)
{
	DateTime a;
	a = "2019-1-1 0:0:0";
	std::cout << a.to_string() << std::endl;
	std::string s = a.to_string();
	BOOST_REQUIRE(s == "2019-1-1 0:0:0");

}

BOOST_AUTO_TEST_CASE(TestDateSubtraction)
{
	// with pen and paper I figured out a bunch of date subtractions(differences)
	// and I'm now testing them vs my DateTime object. the basic format is asserting a - b = c
	// where c is a known difference and a - b are computed by DateTime.
	DateTime a, b, Dab;

	// Date Difference Test #1
	// simple test no borrowing
	a   = "2019-1-1 0:0:0";
	b   = "2018-1-1 0:0:0";
	Dab = "1-0-0 0:0:0";

	BOOST_REQUIRE(a - b == Dab);

	// Date Difference Test #2
	// testing month borrowing
	a   = "2019-1-1 0:0:0";
	b   = "2018-2-1 0:0:0";
	Dab = "0-11-0 0:0:0";

	BOOST_REQUIRE(a - b == Dab);

	//Date Different Test #3
	// testing borrowing of days
	a = "2018-2-1 0:0:0";
	b = "2018-1-2 0:0:0";
	Dab = "0-0-30 0:0:0";
	BOOST_REQUIRE(a - b == Dab);

	//Date Different Test #4
	// testing borrowing of days and month
	a   = "2019-1-1 0:0:0";
	b   = "2018-1-2 0:0:0";
	Dab = "0-11-30 0:0:0";
	BOOST_REQUIRE(a - b == Dab);
}

BOOST_AUTO_TEST_CASE(TestOperatorEqual)
{
	DateTime a, b("2018-1-2 21:55:56");
	a = "2018-1-2 21:55:56";
	BOOST_REQUIRE(a == b);
}

BOOST_AUTO_TEST_SUITE_END()