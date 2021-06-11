#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include "catch.hpp"
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"
#include "Database.h"

TEST_CASE("Add vehicle in database", "[Database]")
{
	Database d;
	Registration reg1("AB1234AB");
	std::string description1 = "car";
	d.addVehicle(reg1, description1);
	REQUIRE(d.numberOfVehicles() == 1);
	REQUIRE(d.getVehicle(0)->plate() == reg1);
	REQUIRE(d.getVehicle(0)->description() == description1);
	SECTION("Throws exception if vehicle with same registration exists")
	{
		REQUIRE_THROWS(d.addVehicle(reg1, description1));
	}
}
TEST_CASE("Add person in database", "[Database]")
{
	Database d;
	std::string name = "Ivan";
	unsigned int id = 1;
	d.addPerson(name,id);
	REQUIRE(d.numberOfPeople() == 1);
	REQUIRE(d.getPerson(0)->name() == name);
	REQUIRE(d.getPerson(0)->id() == id);
	SECTION("Throws exception if person with same id exists")
	{
		REQUIRE_THROWS(d.addPerson(name, id));
	}
}
TEST_CASE("Acquire", "[Database]")
{
	Database d;
	d.addPerson("Ivan", 1);
	d.addPerson("Alexander", 2);
	d.addPerson("Viktor", 3);
	Registration reg1("AB1234AB"), reg2("M6433BT"), reg3("CH2847BH");
	d.addVehicle(reg1, "BMW 320 D");
	d.addVehicle(reg2,"VW Passat 1.9");
	d.addVehicle(reg3,"BMW 320 2.0D+");
	SECTION("Successful")
	{
		d.acquire(1, reg1);
		d.acquire(2, reg2);
		d.acquire(3, reg3);
		REQUIRE(d.getPerson(0)->owns(d.getVehicle(0)));
		REQUIRE(d.getPerson(1)->owns(d.getVehicle(1)));
		REQUIRE(d.getPerson(2)->owns(d.getVehicle(2)));
	}
	SECTION("Throws exception if no owner with id is found")
	{
		REQUIRE_THROWS(d.acquire(4, reg1));
		REQUIRE_THROWS(d.acquire(5, reg2));
	}
	SECTION("Throws exception if no vehicle with registration is found")
	{
		Registration reg4("AB4444BC");
		REQUIRE_THROWS(d.acquire(1, reg4));
		REQUIRE_THROWS(d.acquire(2, reg4));
	}
}
TEST_CASE("Release vehicle", "[Database]")
{
	Database d;
	d.addPerson("Ivan", 1);
	d.addPerson("Alexander", 2);
	d.addPerson("Viktor", 3);
	Registration reg1("AB1234AB"), reg2("M6433BT"), reg3("CH2847BH");
	d.addVehicle(reg1, "BMW 320 D");
	d.addVehicle(reg2, "VW Passat 1.9");
	d.addVehicle(reg3, "BMW 320 2.0D+");
	SECTION("Successful release")
	{
		d.acquire(1, reg1);
		d.acquire(2, reg2);
		d.release(1, reg1);
		d.release(2, reg2);
		REQUIRE(!d.getPerson(0)->owns(d.getVehicle(0)));
		REQUIRE(!d.getPerson(1)->owns(d.getVehicle(1)));
	}
	SECTION("Throws exception if no owner with id is found")
	{
		REQUIRE_THROWS(d.release(4, reg1));
		REQUIRE_THROWS(d.release(5, reg3));
	}
	SECTION("Throws exception if no vehicle with registration is found")
	{
		Registration reg4("TT9999AT");
		REQUIRE_THROWS(d.release(1, reg4));
		REQUIRE_THROWS(d.release(2, reg4));
	}
}
TEST_CASE("Remove vehicle with no owner", "[Database]")
{
	Database d;
	d.addPerson("Ivan", 1);
	Registration reg1("AB1234AB"), reg2("M6433BT");
	d.addVehicle(reg1, "BMW 320 D");
	d.addVehicle(reg2, "VW Passat 1.9");
	d.removeVehicle(reg2);
	REQUIRE(d.numberOfVehicles() == 1);
}
TEST_CASE("Remove vehicle with owner","[Database]")
{
	Database d;
	d.addPerson("Ivan", 1);
	Registration reg1("AB1234AB"), reg2("M6433BT");
	d.addVehicle(reg1, "BMW 320 D");
	d.addVehicle(reg2, "VW Passat 1.9");
	d.acquire(1, reg1);
	d.removeVehicle(reg1);
	REQUIRE(d.numberOfVehicles() == 1);
	REQUIRE(d.getPerson(0)->numberOfVehicles() == 0);
}
TEST_CASE("Remove vehicle doesn't throw exception if no vehicle with this registration is found", "[Database]")
{
	Database d;
	REQUIRE_NOTHROW(d.removeVehicle(Registration("AB1234AB")));
}
TEST_CASE("Remove person with no vehicles", "[Database]")
{
	Database d;
	d.addPerson("Ivan", 1);
	d.removePerson(1);
	REQUIRE(d.numberOfPeople() == 0);
}
TEST_CASE("Remove person with vehicles", "[Database]")
{
	Database d;
	d.addPerson("Ivan", 1);
	Registration reg1("AB1234AB"), reg2("M6433BT");
	d.addVehicle(reg1, "BMW 320 D");
	d.addVehicle(reg2, "VW Passat 1.9");
	d.acquire(1, reg1);
	d.acquire(1, reg2);
	d.removePerson(1);
	REQUIRE(d.numberOfPeople() == 0);
	REQUIRE(d.getVehicle(0)->owner() == nullptr);
	REQUIRE(d.getVehicle(1)->owner() == nullptr);
}
TEST_CASE("Remove person doesn't throw exception if no person with id is found", "[Database]")
{
	Database d;
	REQUIRE_NOTHROW(d.removePerson(2));
}
TEST_CASE("Save to file", "[Database]")
{
	std::string fileName = "data.txt";
	std::string line[] = { "person Peter 2", 
							"person Dimitar 3",
							"vehicle CA7896BT \"Audi A3 1.6\"",
							"ACQUIRE 2 CA7896BT"};

	Database d;
	for (std::size_t i = 0; i < 4; i++)
		d.executeCommand(line[i]);
	d.saveData(fileName);
	std::ifstream ifs(fileName);
	for (std::size_t i = 0; i < 4; i++)
	{
		std::string fileLine;
		std::getline(ifs, fileLine);
		REQUIRE(fileLine == line[i]);
	}
	ifs.close();
}
TEST_CASE("Read from file", "[Database]")
{
	std::string fileName = "input.txt";
	Database d(fileName);
	REQUIRE(d.getPerson(0)->name() == "Peter");
	REQUIRE(d.getPerson(0)->id() == 2);
	REQUIRE(d.getPerson(1)->name() == "Peter Petrov");
	REQUIRE(d.getPerson(1)->id() == 3);
	REQUIRE(d.getVehicle(0)->plate() == Registration("GG9284AA"));
}
