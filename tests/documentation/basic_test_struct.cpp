#define BOOST_TEST_MODULE NameOfTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestName)

BOOST_AUTO_TEST_CASE(TestMethodName)
{
	BOOST_REQUIRE(false);
}

BOOST_AUTO_TEST_SUITE_END()