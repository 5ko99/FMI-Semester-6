#ifndef REG_TESTS
#define REG_TESTS

#include "catch_amalgamated.hpp"
#include <string>
#include <iostream>
using std::string;
using std::ostream;

#include "..\Homework-3.0\Registration.h"

TEST_CASE("Creates default registration number AB1234YZ", "[REGISTRATION]") 
{
	Registration test;
	REQUIRE(test.getNumber() == "AB1234YZ");
}

TEST_CASE("Creates objects and checks if it is valid", "[REGISTRATION]")
{
	Registration test1("C1234AB");
	REQUIRE(test1.isValid());
	Registration test2("XY1111YX");
	REQUIRE(test2.isValid());
	Registration test3("111145");
	REQUIRE(!test3.isValid());
	Registration test4("ABC34DEF");
	REQUIRE(!test4.isValid());
	Registration test5("ABCDEF");
	REQUIRE(!test5.isValid());
	Registration test6("C11D");
	REQUIRE(!test6.isValid());
	Registration test7("AB1234CDE");
	REQUIRE(!test7.isValid());
	Registration test8("AB1234");
	REQUIRE(!test8.isValid());
}

TEST_CASE("== operator working", "[REGISTRATION]")
{
	Registration test1("C1234AB");
	Registration test2("C1234AB");
	Registration test3("C1234A");
	REQUIRE(test1 == test2);
	REQUIRE(!(test1 == test3));
}

#endif
