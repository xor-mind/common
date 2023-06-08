/*
Instructions on setting up a test project for projects in 2023/common

First create a new C++ project.
Then open up the project configurationproperites.

1) ADD THE SOURCE DIRECTORIES:

In VC++ directories -> include directories add
C:\code\2023\common\src
C:\code\2023\common\include

2) ADD THE BOOST HEADERS:

In General -> Additional Include Directories
add "C:\code\2023\lib\boost_1_82_0" to C/C++ ->

3) ADD THE BOOST LIB FILES:

In Linker -> General -> Additional Library directories
add "C:\code\2023\lib\boost_1_82_0\stage\lib"

boost will figure out the right lib to add.

4) Create a new NameTest.cpp and store the file in
C:\code\2023\common\tests with all the other main testing files.

Copy the below code to your NameTest.cpp and Happy Coding!
*/
#define BOOST_TEST_MODULE NameOfTest
#include <boost/test/included/unit_test.hpp>

//#include "CommonFileToInclude.h"

BOOST_AUTO_TEST_SUITE(TestName)

BOOST_AUTO_TEST_CASE(TestMethodName)
{
	BOOST_REQUIRE(false);
}

BOOST_AUTO_TEST_SUITE_END()

