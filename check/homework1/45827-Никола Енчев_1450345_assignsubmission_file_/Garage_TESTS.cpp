
// to use the test coment out main_4.cpp

#include "Garage.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Garage : constructor and copy constructor")
{
	Garage garage1{ 50 };
	Vehicle car{ "123","Big and fast", 42 };

	garage1.insert(car);

	Garage garage2{ garage1 };

	REQUIRE(strcmp(garage1.at(0).getRegistration(), "123") == 0);
	REQUIRE(strcmp(garage1.at(0).getDescription(), "Big and fast") == 0);
	REQUIRE(garage1.at(0).getSpace() == 42);

	SECTION("Testring at function exeption")
	{
		bool exeptionCought = false;

		try {
			garage1.at(2);
		}
		catch (std::out_of_range&) {
			exeptionCought = true;
		}

		REQUIRE(exeptionCought == true);
	}
}
TEST_CASE("Garage : operator []")
{
	Garage garage{ 42 };
	Vehicle car{ "666","Dodge demon",13 };

	garage.insert(car);

	REQUIRE(garage.empty() == false);
	REQUIRE(garage.size() == 1);
	REQUIRE(strcmp(garage[0].getRegistration(), "666") == 0);
	REQUIRE(strcmp(garage[0].getDescription(), "Dodge demon") == 0);
	REQUIRE(garage[0].getSpace() == 13);

}
TEST_CASE("Garage : clear")
{
	Garage garage{ 42 };

	Vehicle car1{ "1111" ,"BMW" , 20 };
	Vehicle car2{ "2222" ,"Audi" , 15 };
	Vehicle car3{ "3333" ,"Mercedes Benz", 5 };

	garage.insert(car1);
	garage.insert(car2);
	garage.insert(car3);

	garage.clear();

	REQUIRE(garage.empty());
	REQUIRE(garage.size() == 0);

	garage.insert(car1);
	garage.insert(car2);
	garage.insert(car3);

	REQUIRE(garage.empty() == false);
	REQUIRE(garage.size() == 3);

}
TEST_CASE("Garage : find")
{
	Garage garage{ 42 };

	Vehicle car1{ "123","ala",10 };
	Vehicle car2{ "456","bala",10 };
	Vehicle car3{ "789","nits",10 };

	garage.insert(car1);
	garage.insert(car2);
	garage.insert(car3);


	REQUIRE(garage.find("123") == &car1);
	REQUIRE(garage.find("456") == &car2);
	REQUIRE(garage.find("789") == &car3);
	REQUIRE(garage.find("111") == nullptr);

	SECTION("Test adding the same vehicle 2 times")
	{
		bool exeptionCought = false;
		try {
			garage.insert(car1);
		}
		catch (std::out_of_range&) {
			exeptionCought = true;
		}

		REQUIRE(exeptionCought == true);
	}
	SECTION("Test overfilling the garage")
	{
		Vehicle car4{ "123","Big Car",40 };

		bool exeptionCought = false;

		try {
			garage.insert(car4);
		}
		catch (std::out_of_range&) {
			exeptionCought = true;
		}

		REQUIRE(exeptionCought == true);
	}

}
TEST_CASE("Garage : erase")
{
	Garage garage{ 24 };

	Vehicle car1{ "123","abc",10 };
	Vehicle car2{ "345","cde",3 };
	Vehicle car3{ "567","efg",7 };

	garage.insert(car1);
	garage.insert(car2);
	garage.insert(car3);

	garage.erase("123");
	REQUIRE(garage.find("123") == nullptr);
	REQUIRE(garage.size() == 2);
	REQUIRE(garage.at(0).getSpace() == car2.getSpace());
}
