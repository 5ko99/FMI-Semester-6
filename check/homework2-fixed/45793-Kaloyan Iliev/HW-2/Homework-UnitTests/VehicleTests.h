#ifndef VEH_TESTS
#define VEH_TESTS

#include "catch_amalgamated.hpp"

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;

#include "..\Homework-3.0\Common.h"

TEST_CASE("Creates object by reg num and desc, no owner yet", "[VEHICLE]") //assume correct parameters, they will be checked by a seperate input parser
{
	Registration reg1("CA1234XY");
	string desc1("exploding cat");
	Vehicle car(reg1, desc1);
	REQUIRE(car.getReg() == reg1);
	REQUIRE(car.getDes() == desc1);
	REQUIRE(car.owner == nullptr);
}

TEST_CASE("Adding an owner", "[VEHICLE]")
{
	Registration reg1("X6996XX");
	string desc1("incarnation cat");
	Vehicle car(reg1, desc1);
	Person human("Cool person", 420);
	car.addOwner(&human);
	REQUIRE(car.owner);
}

TEST_CASE("operator==, used to compare reg nums, same reg nums = same veh, 10/10 logic, maybe TODO fix", "[VEHICLE]")
{
	Registration reg1("X6996XX");
	Registration reg2("Y9669YY");
	Vehicle car1(reg1, "smthng");
	Vehicle car2(reg1, "smthng");
	Vehicle car3(reg1, "else");
	Vehicle car4(reg2, "else");
	REQUIRE(car1 == car2);
	REQUIRE(car1 == car3);
	REQUIRE(car2 == car3);
	REQUIRE(!(car3 == car4));
	REQUIRE(!(car1 == car4));
}

#endif
