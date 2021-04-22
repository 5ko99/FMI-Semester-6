#pragma
#include "catch2.hpp";
#include "../HOMEWORK_82037/MyString.h"

TEST_CASE("Incorect position", "[mystring]")
{
	MyString a1="ABCDEFG";

	REQUIRE(a1.at(5) == 'F');
	REQUIRE(a1.at(6) == 'G');
	REQUIRE(a1.at(0) == 'A');
	REQUIRE(a1.at(1) == 'B');

	REQUIRE(a1[5] == 'F');
	REQUIRE(a1[6] == 'G');
	REQUIRE(a1[0] == 'A');
	REQUIRE(a1[8] == 'B');



	REQUIRE(a1.front() == 'A');
	REQUIRE(a1.back() == 'G');

	
}