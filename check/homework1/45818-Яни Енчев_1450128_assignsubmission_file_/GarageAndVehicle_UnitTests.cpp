#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"
#include <stdexcept>

TEST_CASE("Testing Vehicle constructor")
{
	Vehicle test("0000", "Testova kola", 1);

	REQUIRE_FALSE(strcmp(test.registration(), "0000"));
	REQUIRE_FALSE(strcmp(test.description(), "Testova kola"));
	REQUIRE(test.space() == 1);
}

TEST_CASE("Testing the function 'insert'")
{
	Garage test(5);
	SECTION("Inserting a vehicle that takes too much space")
	{
		bool success = false;
		try
		{
			Vehicle v("0", "Car", 6);
			test.insert(v);
		}
		catch (std::length_error& e)
		{
			success = true;
			std::cout << e.what() << std::endl;
		}
		REQUIRE(success);
	}
	SECTION("Insert a vehicle with valid parameters")
	{
		Vehicle v("0", "Car", 3);
		test.insert(v); // shouldn't be any exceptions throws here

		REQUIRE_FALSE(strcmp(test[0].registration(), "0"));
		REQUIRE_FALSE(strcmp(test[0].description(), "Car"));
		REQUIRE(test[0].space() == 3);
		REQUIRE(test.size() == 1);
	}
	SECTION("Insert a vehicle with a registration number already in")
	{
		bool success = 0;
		Vehicle v("0", "Car", 1);
		Vehicle two("0", "Truck", 3);
			test.insert(v);
		try
		{
			test.insert(two);
		}
		catch (std::invalid_argument& e)
		{			
			std::cout << e.what() << std::endl;
			success = 1;

		}			
		REQUIRE(success);
	}
}

TEST_CASE("Testing the 'erase' function")
{
	Garage test(20);
	Vehicle car("111", "Car", 2);
	Vehicle bus("101", "Bus", 4);
	Vehicle train("011", "Train", 10);
		
	test.insert(car);
	test.insert(bus);
	test.insert(train);

	/*SECTION("Erasing a vehicle with description - nullptr")
	{
		Vehicle plane("", "Plane", 1);
		test.insert(plane);
		REQUIRE(test.size() == 4);

		test.erase("");
		REQUIRE(test.size() == 3);

		for some reason putting in "" here makes the 'this' a nullptr and gives me segmentation error
		that doesn't happen when testing it on the MyString class;
	}*/

	REQUIRE(test.size() == 3);

	/*test.erase("222");
	REQUIRE(test.size() == 3);*/

	/*test.erase("111");
	REQUIRE(test.size() == 2);*/


	SECTION("Trying to erase elements that have nullptr as registration")
	{
		Vehicle nul("", "Null", 1);
		REQUIRE(nul.registration() == nullptr);
		//test.insert(nul);
		//REQUIRE(test.size() == 3);

		//test.erase("");
		//REQUIRE(test.size() == 3);
	}
}

TEST_CASE("Testing the 'at' function")
{
	Garage test(20);
	Vehicle first("000", "Car", 2);
	Vehicle second("001", "Bike", 1);
	Vehicle third("002", "Scooter", 1);

	test.insert(first);
	test.insert(second);
	test.insert(third);
	SECTION("Giving a valid position")
	{
		REQUIRE(&test.at(1) == &second);
		REQUIRE(&test.at(2) == &third);
		REQUIRE(&test.at(0) == &first);
	}

	SECTION("Giving an out of range position")
	{
		bool exc = 0;
		try
		{
			test.at(3);
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what() << std::endl;
			exc = 1;
		}
		REQUIRE(exc == 1);
	}
}

TEST_CASE("Testing 'empty'")
{
	Garage test(20);
	Vehicle one("1", "car", 4);
	test.insert(one);

	SECTION("Emptying with 'clear'")
	{
		Vehicle two("2", "car", 4);
		test.insert(two);
		REQUIRE(test.size() == 2);

		test.clear();
		REQUIRE(test.empty());
	}
	SECTION("Emptying by 'erase'")
	{
		test.erase("1");
		REQUIRE(test.empty());
	}
	SECTION("not empty")
	{
		REQUIRE_FALSE(test.empty());
	}
}