#ifndef PERSON_TESTS
#define PERSON_TESTS

#include "catch_amalgamated.hpp"

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;

#include "..\Homework-3.0\Common.h"

TEST_CASE("Creates object by name and id", "[PERSON]") //assume correct parameters, they will be checked by a seperate input parser
{
	Person test1("Ivan", 69);
	REQUIRE(test1.getName() == "Ivan");
	REQUIRE(test1.getId() == 69);
	REQUIRE(test1.getVehCnt() == 0);
}

TEST_CASE("Add vehicle to a person", "[PERSON]")
{
	// add 1 vehicle
	Registration reg1("AB1234YZ");
	string desc1("car 1");
	Vehicle car1(reg1, desc1);
	Person person1("Ivan", 420);
	person1.addVehicle(&car1);
	Registration regToBeTested = person1.getVehicle(0)->getReg();
	REQUIRE(person1.getVehicle(0)->getDes() == "car 1");
	REQUIRE(person1.getVehicle(0)->getReg() == reg1);
	REQUIRE(person1.getVehCnt() == 1);

	// add 2 vehicles
	Registration reg2("C5432HY");
	string desc2("car 2");
	Vehicle car2(reg2, desc2);
	person1.addVehicle(&car2);
	REQUIRE(person1.getVehicle(1)->getDes() == "car 2");
	REQUIRE(person1.getVehicle(1)->getReg() == reg2);
	REQUIRE(person1.getVehCnt() == 2);
}

TEST_CASE("Remove vehicle", "[PERSON]") 
{
	Registration reg1 = "A1234BC";
	string desc1 = "car1";
	Registration reg2 = "CA1434CB";
	string desc2 = "car2";
	Vehicle veh1(reg1, desc1);
	Vehicle veh2(reg2, desc2);
	Person person1("Gosho", 1);
	person1.addVehicle(&veh1);
	person1.addVehicle(&veh2);
	person1.removeVehicle(veh1);
	REQUIRE(person1.getVehCnt() == 1);
	person1.removeVehicle(veh2);
	REQUIRE(person1.getVehCnt() == 0);
}


#endif
