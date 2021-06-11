#define CATCH_CONFIG_MAIN 
#include <cassert>
#include "catch2.hpp"
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"
#include "Database.h"

TEST_CASE("Registration Constructor", "[Registration]")
{
	SECTION("Registration_GivenValidString_Create")
	{
		Registration reg("AB1234BA");

		REQUIRE(reg.toString() == "AB1234BA");
	}
	SECTION("Registration_GivenInvalidString_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Registration("A1234B"), std::invalid_argument);
	}
}

TEST_CASE("Vehicle Constructor", "[Vehicle]")
{
	SECTION("Vehicle_GivenDefault_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Vehicle(), std::invalid_argument);
	}
	SECTION("Vehicle_GivenInvalid_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Vehicle("A1234B", "audi"), std::invalid_argument);
	}
	SECTION("Vehicle_GivenValid_Create")
	{
		Vehicle veh("AB1234BA", "audi");
		REQUIRE(veh.getRegistration() == "AB1234BA");
		REQUIRE(veh.getDescription() == "audi");
		REQUIRE(veh.getOwnerID() == 0);
	}
}

TEST_CASE("Vehicle setOwnerID class method", "[setOwnerID]")
{
	SECTION("setOwnerID_GivenID_Set")
	{
		Vehicle veh("AB1234BA", "audi");
		veh.setOwnerID(5);
		REQUIRE(veh.getOwnerID() == 5);
	}
}

TEST_CASE("Person Constructor", "[Person]")
{
	SECTION("Person_GivenDefault_Zero")
	{
		Person p;
		REQUIRE(p.getName() == "");
		REQUIRE(p.getID() == 1);
		REQUIRE(p.getVehicleCount() == 0);
	}
	SECTION("Person_GivenValid")
	{
		Person p("Ivan", 256);
		REQUIRE(p.getName() == "Ivan");
		REQUIRE(p.getID() == 256);
		p.addVehicle("AB1234BA");
		REQUIRE(p.getVehicleCount() == 1);
		REQUIRE(p.getAtIndex(0) == "AB1234BA");
	}
}

TEST_CASE("Person addVehicle class method", "[addVehicle]")
{
	SECTION("addVehicle_GivenVehicle_Add")
	{
		Person p("Ivan", 256);
		p.addVehicle("AB1234BA");
		REQUIRE(p.getAtIndex(0) == "AB1234BA");
	}
}

TEST_CASE("Person removeVehicle class method", "[removeVehicle]")
{
	SECTION("removeVehicle_GivenVehicle_Remove")
	{
		Person p("Ivan", 256);
		p.addVehicle("AB1234BA");
		p.removeVehicle("AB1234BA");
		REQUIRE(p.getVehicleCount() == 0);
	}
}

TEST_CASE("Person findVehicle class method", "[findVehicle]")
{
	SECTION("findVehicle_GivenVehicle_ReturnValidInd")
	{
		Person p("Ivan", 256);
		p.addVehicle("AB1234BA");
		REQUIRE(p.findVehicle("AB1234BA") == 0);
	}
	SECTION("findVehicle_GivenInvalidVehicle_Return-1")
	{
		Person p("Ivan", 256);
		REQUIRE(p.findVehicle("AB1234BA") == -1);
		p.addVehicle("AB1234BA");
		REQUIRE(p.findVehicle("XY1234YX") == -1);
	}
}

TEST_CASE("Database addPerson class method", "[addPerson]")
{
	SECTION("addPerson_GivenPerson_Add")
	{
		Database::i().addPerson("Ivan", 256);
		REQUIRE(Database::i().findPerson(256) == 0);
	}
	SECTION("addPerson_GivenSamePerson_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Database::i().addPerson("Ivan", 256), std::invalid_argument);
	}
}

TEST_CASE("Database removePerson class method", "[removePerson]")
{
	SECTION("removePerson_GivenPerson_Remove")
	{
		Database::i().removePerson(256);
		REQUIRE(Database::i().findPerson(256) == -1);
	}
	SECTION("removePerson_GivenSamePerson_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Database::i().removePerson(256), std::invalid_argument);
	}
}

TEST_CASE("Database findPerson class method", "[findPerson]")
{
	SECTION("findPerson_GivenPerson_ValidIndex")
	{
		Database::i().addPerson("Ivan", 256);
		REQUIRE(Database::i().findPerson(256) == 0);
	}
	SECTION("findPerson_GivenSamePerson_InvalidIndex")
	{
		Database::i().removePerson(256);
		REQUIRE(Database::i().findPerson(256) == -1);
	}
}

TEST_CASE("Database addVehicle class method", "[addVehicle]")
{
	SECTION("addVehicle_GivenVehicle_Add")
	{
		Database::i().addVehicle("AB1234BA", "audi");
		REQUIRE(Database::i().findVehicle("AB1234BA") == 0);
	}
	SECTION("addVehicle_GivenSameVehicle_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Database::i().addVehicle("AB1234BA", "audi"), std::invalid_argument);
	}
}

TEST_CASE("Database deleteVehicle class method", "[deleteVehicle]")
{
	SECTION("deleteVehicle_GivenVehicle_Remove")
	{
		Database::i().deleteVehicle("AB1234BA");
		REQUIRE(Database::i().findVehicle("AB1234BA") == -1);
	}
	SECTION("deleteVehicle_GivenSameVehicle_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Database::i().deleteVehicle("AB1234BA"), std::invalid_argument);
	}
}

TEST_CASE("Database findVehicle class method", "[findVehicle]")
{
	SECTION("findVehicle_GivenVehicle_ValidIndex")
	{
		Database::i().addVehicle("AB1234BA", "audi");
		REQUIRE(Database::i().findVehicle("AB1234BA") == 0);
	}
	SECTION("findVehicle_GivenSameVehicle_InvalidIndex")
	{
		Database::i().deleteVehicle("AB1234BA");
		REQUIRE(Database::i().findVehicle("AB1234BA") == -1);
	}
}

TEST_CASE("Database acquire class method", "[acquire]")
{
	SECTION("acquire_GivenInvalidPerson_ShouldThrow")
	{
		Database::i().addVehicle("AB1234BA", "audi");
		REQUIRE_THROWS_AS(Database::i().acquire(256, "AB1234BA"), std::invalid_argument);
	}
	SECTION("acquire_GivenInvalidVehicle_ShouldThrow")
	{
		Database::i().deleteVehicle("AB1234BA");
		Database::i().addPerson("Ivan", 256);
		REQUIRE_THROWS_AS(Database::i().acquire(256, "AB1234BA"), std::invalid_argument);
	}
}

TEST_CASE("Database release class method", "[release]")
{
	SECTION("release_GivenInvalidPerson_ShouldThrow")
	{
		Database::i().removePerson(256);
		Database::i().addVehicle("AB1234BA", "audi");
		REQUIRE_THROWS_AS(Database::i().release(256, "AB1234BA"), std::invalid_argument);
	}
	SECTION("release_GivenInvalidVehicle_ShouldThrow")
	{
		Database::i().deleteVehicle("AB1234BA");
		Database::i().addPerson("Ivan", 256);
		REQUIRE_THROWS_AS(Database::i().release(256, "AB1234BA"), std::invalid_argument);
	}
}

TEST_CASE("Database writeToFile class method", "[writeToFile]")
{
	SECTION("writeToFile_GivenFile_Save")
	{
		Database::i().addVehicle("AB1234BA", "audi");
		Database::i().acquire(256, "AB1234BA");
		Database::i().writeToFile("file.txt");
		Database::i().removePerson(256);
		Database::i().deleteVehicle("AB1234BA");
		Database::i().readFromFile("file.txt");
		REQUIRE(Database::i().findPerson(256) == 0);
		REQUIRE(Database::i().findVehicle("AB1234BA") == 0);
	}
}

TEST_CASE("Database readFromFile class method", "[readFromFile]")
{
	SECTION("readFromFile_GivenValidFile_Load")
	{
		Database::i().removePerson(256);
		Database::i().deleteVehicle("AB1234BA");
		Database::i().readFromFile("file.txt");
		REQUIRE(Database::i().findPerson(256) == 0);
		REQUIRE(Database::i().findVehicle("AB1234BA") == 0);
	}
	SECTION("readFromFile_GivenInvalidFile_ShouldThrow")
	{
		REQUIRE_THROWS_AS(Database::i().readFromFile("abc.txt"), std::invalid_argument);
	}
}
