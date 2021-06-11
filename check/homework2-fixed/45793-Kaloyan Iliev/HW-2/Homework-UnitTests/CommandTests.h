#ifndef CMD_TESTS
#define CMD_TESTS

#include "catch_amalgamated.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;
#include "..\Homework-3.0\Common.h"
#include "..\Homework-3.0\Command.h"
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;


// for simplicity I made the members vector<Person> People and vector<Vehicle> Vehicles
// public and accessed them directly
TEST_CASE("Add vehicle", "[COMMAND]")
{
	Command driver;
	REQUIRE(driver.Vehicles.size() == 0);
	REQUIRE(driver.People.size() == 0);
	Registration reg1("CA1234YZ");
	
	driver.addVehicle(reg1, "bus");
	REQUIRE(driver.Vehicles.size() == 1);
	REQUIRE(driver.Vehicles[0].getReg() == reg1);
	REQUIRE(driver.Vehicles[0].getDes() == "bus");
	REQUIRE(driver.Vehicles[0].owner == nullptr);
}

TEST_CASE("Add person", "[COMMAND]")
{
	Command driver;
	driver.addPerson("Pesho", 8);
	REQUIRE(driver.People.size() == 1);
	REQUIRE(driver.People[0].getName() == "Pesho");
	REQUIRE(driver.People[0].getId() == 8);
	REQUIRE(driver.People[0].getVehCnt() == 0);
}

TEST_CASE("Person acquire vehicle", "[COMMAND]")
{
	Command driver;
	driver.addPerson("Pesho", 8);
	Registration reg1("CA1234YZ");
	driver.addVehicle(reg1, "bus");
	driver.acquire(8, reg1);
	REQUIRE(driver.People[0].getVehCnt() == 1);

	Registration reg2("A1234YZ");
	driver.addVehicle(reg2, "car");
	driver.acquire(8, reg2);
	REQUIRE(driver.People[0].getVehCnt() == 2);
}

TEST_CASE("Person acquire vehicle, vehicle has current owner so we test release function too", "[COMMAND]")
{
	Command driver;
	driver.addPerson("Owner", 8);
	driver.addPerson("newOwner", 9);
	Registration reg1("CA1234YZ");
	driver.addVehicle(reg1, "car");
	driver.acquire(8, reg1);
	driver.acquire(9, reg1);
	REQUIRE(driver.People[0].getVehCnt() == 0);
	REQUIRE(driver.People[1].getVehCnt() == 1);
	REQUIRE(driver.Vehicles[0].owner == &driver.People[1]);
}

TEST_CASE("Delete person") 
{
	Command driver;
	driver.addPerson("Ivan", 1);
	driver.addPerson("Gosho", 2);
	driver.addPerson("Pesho", 3);
	Registration reg1("CA1234YZ");
	Registration reg2("A1234YZ");
	Registration reg3("B4321YZ");
	driver.addVehicle(reg1, "C1");
	driver.addVehicle(reg2, "C2");
	driver.addVehicle(reg3, "C3");
	driver.acquire(1, reg1);
	driver.acquire(2, reg2);
	//driver.acquire(3, reg3); REQUIRES work if you confirm but not if you don't (intended)
	driver.remove(3);
	REQUIRE(driver.People.size() == 2);
	REQUIRE(driver.Vehicles.size() == 3);
}

TEST_CASE("Delete vehicle")
{
	Command driver;
	driver.addPerson("Ivan", 1);
	driver.addPerson("Gosho", 2);
	driver.addPerson("Pesho", 3);
	Registration reg1("CA1234YZ");
	Registration reg2("A1234YZ");
	Registration reg3("B4321YZ");
	driver.addVehicle(reg1, "C1");
	driver.addVehicle(reg2, "C2");
	driver.addVehicle(reg3, "C3");
	driver.acquire(1, reg1);
	driver.acquire(2, reg2);
	//driver.acquire(3, reg3); 
	driver.remove(reg3);
	REQUIRE(driver.People.size() == 3);
	REQUIRE(driver.Vehicles.size() == 2);
	driver.remove(reg2);
	REQUIRE(driver.People.size() == 3);
	REQUIRE(driver.Vehicles.size() == 1);
}

// here I start testing without catch2 using just a cpp file with a main and playing around.
// reason is because of output to text files in <save> function and output to console in <show> functions

#endif
