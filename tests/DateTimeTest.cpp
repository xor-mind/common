#define BOOST_TEST_MODULE DateTimeTest
#include <boost/test/included/unit_test.hpp>

#include "DateTime.h"

BOOST_AUTO_TEST_SUITE(TestDateTime)

BOOST_AUTO_TEST_CASE(TestToString)
{
	DateTime a;
	a = "2019-1-1 0:0:0";
	//std::cout << a.to_string() << std::endl;
	std::string s = a.to_string();
	BOOST_REQUIRE(s == "2019-1-1 0:0:0");

}

BOOST_AUTO_TEST_CASE(TestDateAddition)
{
	DateTime a, b, Sab;
	// Date Addition Test #1
	// simple case/test -  no carrying
	{
		a = "2019-1-1 1:1:1";
		b = "0-0-0 1:5:6";
		Sab = "2019-1-1 2:6:7"; // let Sab = "the sum of dateTime A and delta B" = dateTime

		BOOST_REQUIRE(a + b == Sab);
	}

	// Date Addition Tests #2
	// carrying test for seconds
	{
		// Test #2 - 1
		a = "2019-1-1 0:0:1";
		b = "0-0-0 0:0:59";
		Sab = "2019-1-1 0:1:0";

		BOOST_REQUIRE(a + b == Sab);

		// Test #2 - 2
		a = "2019-1-1 0:0:59";
		b = "0-0-0 0:0:59";
		Sab = "2019-1-1 0:1:58";

		BOOST_REQUIRE(a + b == Sab);

		// Test #2 - 3
		a = "2019-1-1 0:25:59";
		b = "0-0-0 0:0:17";
		Sab = "2019-1-1 0:26:16";

		BOOST_REQUIRE(a + b == Sab);
	}

	// Date Addition Tests #3
	// carrying test for minutes
	{
		// Test #3 - 1
		a = "2019-1-1 0:53:50";
		b = "0-0-0 3:7:2";
		Sab = "2019-1-1 4:0:52";

		BOOST_REQUIRE(a + b == Sab);

		// Test #3 - 2
		a = "2019-1-1 2:58:1";
		b = "0-0-0 7:43:0";
		Sab = "2019-1-1 10:41:1";

		BOOST_REQUIRE(a + b == Sab);

		// Test #3 - 3
		a = "2019-1-1 0:50:0";
		b = "0-0-0 0:51:0";
		Sab = "2019-1-1 1:41:0";

		BOOST_REQUIRE(a + b == Sab);
	}

	// Date Addition Tests #4
	// carrying test for hours
	{
		// Test #4 - 1
		a = "2019-1-1 11:0:0";
		b = "0-0-0 22:0:0";
		Sab = "2019-1-2 9:0:0";

		BOOST_REQUIRE(a + b == Sab);

		// Test #4 - 2
		a = "2019-1-28 22:0:0";
		b = "0-0-0 7:0:0";
		Sab = "2019-1-29 5:0:0";

		BOOST_REQUIRE(a + b == Sab);

		//// Test #3 - 3
		//a = "2019-1-1 0:50:0";
		//b = "0-0-0 0:51:0";
		//Sab = "2019-1-1 1:41:0";

		//BOOST_REQUIRE(a + b == Sab);
	}

	// Date Addition Test #5
	// carrying test for days
	{
		// Test #5 - 1
		a = "2019-1-31 0:0:0";
		b = "0-0-1 0:0:0";
		Sab = "2019-2-1 0:0:0";
		BOOST_REQUIRE(a + b == Sab);

		// Test #5 - 2
		a = "2019-2-28 0:0:0";
		b = "0-0-1 0:0:0";
		Sab = "2019-3-1 0:0:0";
		BOOST_REQUIRE(a + b == Sab);

		a = "2019-10-31 0:0:0";
		b = "0-0-1 0:0:0";
		Sab = "2019-11-1 0:0:0";
		BOOST_REQUIRE(a + b == Sab);

		a = "2019-1-31 0:0:0";
		b = "0-0-31 0:0:0";
		Sab = "2019-11-1 0:0:0";
		BOOST_REQUIRE(a + b == Sab);
	}

	// Date Addition Test #6
	// carrying test for months
	//{
	//	// Test #6 - 1
	//	a = "2019-1-31 0:0:0";
	//	b = "0-0-1 0:0:0";
	//	Sab = "2019-2-1 0:0:0";
	//	BOOST_REQUIRE(a + b == Sab);

	//}
	//

	////Date Different Test #3
	//// testing borrowing of days
	//a = "0-5-1 0:0:0";
	//b = "0-1-2 0:0:0";
	//Dab = "0-3-29 0:0:0";
	//BOOST_REQUIRE(a - b == Dab);

	////Date Different Test #4
	//// testing borrowing of days and month
	//a = "2019-1-1 0:0:0";
	//b = "2018-1-2 0:0:0";
	//Dab = "0-11-30 0:0:0";
}

BOOST_AUTO_TEST_CASE(TestDateSubtractionYearMonthDay)
{
	// with pen and paper I figured out a bunch of date subtractions(differences)
	// and I'm now testing them vs my DateTime object. the basic format is asserting a - b = c
	// where c is a known difference and a - b are computed by DateTime.
	DateTime a, b, Dab;

	// 111
	//   2

	//// quick test case I was thinking of
	//a = "2019-1-1 0:0:0";
	//b = "2019-1-1 0:0:0";
	//Dab = "1-0-0 0:0:0";

	//BOOST_REQUIRE(a - b == Dab);

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
	a = "0-5-1 0:0:0";
	b = "0-1-2 0:0:0";
	Dab = "0-3-29 0:0:0";
	BOOST_REQUIRE(a - b == Dab);

	//Date Different Test #4
	// testing borrowing of days and month
	a   = "2019-1-1 0:0:0";
	b   = "2018-1-2 0:0:0";
	Dab = "0-11-30 0:0:0";
	BOOST_REQUIRE(a - b == Dab);
}

BOOST_AUTO_TEST_CASE(TestDateSubtractionHourMinuteSecond)
{
	// with pen and paper I figured out a bunch of date subtractions(differences)
	// and I'm now testing them vs my DateTime object. the basic format is asserting a - b = c
	// where c is a known difference and a - b are computed by DateTime.
	DateTime a, b, Dab;

	// Date Difference Test #1
	// simple test no borrowing
	a = "2019-1-1 3:20:5";
	b = "2019-1-1 2:19:4";
	Dab = "0-0-0 1:1:1";
	BOOST_REQUIRE(a - b == Dab);

	// Date Difference Test #2
	// testing second borrowing
	a = "2019-1-1 0:1:1";
	b = "2019-1-1 0:0:59";
    Dab = "0-0-0 0:0:2";
	BOOST_REQUIRE(a - b == Dab);

	//Date Different Test #3
	// testing minute borrowing
	a = "2019-1-1 1:1:0";
	b = "2019-1-1 0:2:0";
	Dab = "0-0-0 0:59:0";
	BOOST_REQUIRE(a - b == Dab);

	//Date Different Test #4
	// testing hour borrowing
	a = "2019-1-2 1:0:0";
	b = "2019-1-1 2:0:0";
	Dab = "0-0-0 23:0:0";
	BOOST_REQUIRE(a - b == Dab);

	// lots of borrowing #1
	a = "2019-1-3 1:19:25";
	b = "2018-2-5 2:25:43";
	Dab = "0-10-28 22:53:42";
	BOOST_REQUIRE(a - b == Dab);

	// another test I want
	a = "2019-5-2 0:0:0";
	b = "2019-4-2 0:0:0";
	Dab = "0-1-0 0:0:0";
	BOOST_REQUIRE(a - b == Dab);
}

BOOST_AUTO_TEST_CASE(TestOperatorEqual)
{
	DateTime a, b("2018-1-2 21:55:56");
	a = "2018-1-2 21:55:56";
	BOOST_REQUIRE(a == b);
}

BOOST_AUTO_TEST_SUITE_END()