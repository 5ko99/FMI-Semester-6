#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>
#include "console.h"
#include "commandNotFoundException.h"
#include "invalidNumberOfArgumentsException.h"
#include "commandLineParser.h"
#include "vehicleCommand.h"
#include "personCommand.h"
#include "acquireCommand.h"
#include "releaseCommand.h"
#include "removeCommand.h"
#include "saveCommand.h"
#include "showCommand.h"
#include "loadCommand.h"


TEST_CASE("Test registration")
{
	SECTION("empty object")
	{
		Registration r1;
		REQUIRE(r1.getData() == "");
	}

	SECTION("object with registration")
	{
		Registration r2("UK7777LO");
		REQUIRE(r2.getData() == "UK7777LO");
	}

	SECTION("Test operator ==")
	{
		Registration r3("BG9999PL");
		Registration r4("BG9999PL");

		REQUIRE(r3 == r4);

		Registration r5("I7777OP");

		REQUIRE(!(r3 == r5));
	}
}

TEST_CASE("Test vehicle")
{
	Vehicle v({"SO8888UL"}, "red car");

	SECTION("Test registration number")
	{
		REQUIRE(v.getRegistrationNumber().getData() == "SO8888UL");
	}

	Person p("pesho", 1);
	v.setOwner(&p);

	SECTION("Set owner")
	{
		REQUIRE(v.getOwner() == &p);
	}

	SECTION("Set owner-nullptr")
	{
		v.setOwner(nullptr);
		REQUIRE(v.getOwner() == nullptr);
	}
}

TEST_CASE("Test person")
{
	Person p("pesho", 89);
	REQUIRE(p.getId() == 89);

	SECTION("change id")
	{
		p.setId(12);
		REQUIRE(p.getId() == 12);
	}

	Vehicle v({"UK9999QW"}, "red car");

	SECTION("buy and release")
	{
		p.buyVehicle(v);
		REQUIRE(p.getVehicles().operator[](0) == &v);
		REQUIRE(p.getVehicles().size() == 1);

		p.releaseVehicle(v.getRegistrationNumber());
		REQUIRE(p.getVehicles().size() == 0);
	}
}

TEST_CASE("Test command line parser")
{
	SECTION("Test split command")
	{
		std::string line1 = "Hello world! abc     \"Ivan   Petrov\"    hahah";
		//std::cout << line1 << std::endl;
		std::vector<std::string> parts1 = CommandLineParser::split(line1, ' ');
		std::vector<std::string> parts2 = CommandLineParser::split(line1, '!');
		std::vector<std::string> parts3 = CommandLineParser::split(line1, '#');
		/*for (auto i : parts1)
		{
			std::cout << i << std::endl;
		}*/

		SECTION("test size")
		{
			REQUIRE(parts1.size() == 5);

			REQUIRE(parts2.size() == 2);
			REQUIRE(parts3.size() == 1);
		}

		SECTION("test splitting")
		{
			REQUIRE(parts1[0] == "Hello");
			REQUIRE(parts1[1] == "world!");

			REQUIRE(parts2[0] == "Hello world");
			REQUIRE(parts2[0].size() == 11);

			REQUIRE(parts3[0] == "Hello world! abc     \"Ivan   Petrov\"    hahah");
		}
	}

	SECTION("Test person id")
	{
		REQUIRE(CommandLineParser::isPersonId("5"));
		REQUIRE(CommandLineParser::isPersonId("12"));
		REQUIRE(!CommandLineParser::isPersonId("wq"));
		REQUIRE(!CommandLineParser::isPersonId("m"));
	}

	SECTION("Test vehicle id")
	{
		Vehicle v({"CC1111EE"}, "car");
		REQUIRE(CommandLineParser::isVehicleId(v.getRegistrationNumber().getData()));

		REQUIRE(CommandLineParser::isVehicleId("UK4444KL"));
		REQUIRE(CommandLineParser::isVehicleId("U7777KL"));
		REQUIRE(!CommandLineParser::isVehicleId("asdf"));
	}
}

TEST_CASE("Test system")
{
	System s;
	s.addPerson({"pesho", 1});
	s.addPerson({"gosho", 9});


	
	SECTION("Test add person")
	{
		REQUIRE(s.getPersonById(1) == 0);
		REQUIRE(s.getPersonById(9) == 1);
	}

	s.addVehicle({{"UK9999LO"}, "red car"});
	s.addVehicle({{"UK5555LO"}, "big car"});
	s.addVehicle({{"UK1111LO"}, "truck"});

	SECTION("Test add vehicle")
	{	
		s.addVehicle({{"NL1111LI"}, "bus"});

		REQUIRE(s.getVehicleById({"UK9999LO"}) == 0);
		REQUIRE(s.getVehicleById({"UK5555LO"}) == 1);
		REQUIRE(s.getVehicleById({"UK1111LO"}) == 2);
		REQUIRE(s.getVehicleById({"NL1111LI"}) == 3);
	}


	Vehicle v1({"NL1111KI"}, "black car");
	s.addVehicle(v1);

	Person p1("yana", 109);
	s.addPerson(p1);
	s.setOwner(v1, p1);

	SECTION("Test set owner")
	{
		REQUIRE(v1.getOwner() == &p1);
	}

	SECTION("Test indexing for vehicle")
	{
		REQUIRE(s.vehicleAt(3).getRegistrationNumber().getData() == "NL1111KI");
		REQUIRE(s.vehicleAt(2).getRegistrationNumber().getData() == "UK1111LO");
		REQUIRE(s.vehicleAt(1).getRegistrationNumber().getData() == "UK5555LO");
		REQUIRE(s.vehicleAt(0).getRegistrationNumber().getData() == "UK9999LO");

	}

	SECTION("Test indexing for people")
	{
		REQUIRE(s.personAt(2).getId() == 109);
		REQUIRE(s.personAt(1).getId() == 9);
		REQUIRE(s.personAt(0).getId() == 1);
	}
	
}
