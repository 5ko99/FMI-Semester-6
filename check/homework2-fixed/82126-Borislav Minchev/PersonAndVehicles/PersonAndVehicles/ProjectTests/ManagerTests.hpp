#pragma once

#include "catch.hpp"
#include "../PersonAndVehicles/PersonAndVehicleManager.h"

SCENARIO("Testing creating new persons and vehicles")
{
	GIVEN("Empty manger object")
	{
		PersonAndVehicleManager manager;
		WHEN("We try to create some persons with different id-s")
		{
			THEN("No exeptions are thrown and everything is set correctly")
			{
				REQUIRE_NOTHROW(manager.newPerson(1, "abc"));
				REQUIRE_NOTHROW(manager.newPerson(2, "def"));
				REQUIRE_NOTHROW(manager.newPerson(3, "ghi"));

				REQUIRE(manager.getAllPersons().size() == 3);

				REQUIRE(manager.getAllPersons()[0].getId() == 1);
				REQUIRE(manager.getAllPersons()[0].getName() == "abc");

				REQUIRE(manager.getAllPersons()[1].getId() == 2);
				REQUIRE(manager.getAllPersons()[1].getName() == "def");

				REQUIRE(manager.getAllPersons()[2].getId() == 3);
				REQUIRE(manager.getAllPersons()[2].getName() == "ghi");

			}
		}
		WHEN("We try to create some vehicles with different registration numbers")
		{
			THEN("No exeptions are thrown and everything is set correctly")
			{
				REQUIRE_NOTHROW(manager.newVehicle("AA1234BB", "abc"));
				REQUIRE_NOTHROW(manager.newVehicle("CC1234DD", "def"));
				REQUIRE_NOTHROW(manager.newVehicle("EE1234FF", "ghi"));

				REQUIRE(manager.getAllVehicles().size() == 3);
								  
				REQUIRE(manager.getAllVehicles()[0].getRegistration().getRegistrationString() == "AA1234BB");
				REQUIRE(manager.getAllVehicles()[0].getDescription() == "abc");
								  
				REQUIRE(manager.getAllVehicles()[1].getRegistration().getRegistrationString() == "CC1234DD");
				REQUIRE(manager.getAllVehicles()[1].getDescription() == "def");
								   
				REQUIRE(manager.getAllVehicles()[2].getRegistration().getRegistrationString() == "EE1234FF");
				REQUIRE(manager.getAllVehicles()[2].getDescription() == "ghi");

			}
		}
	}

	GIVEN("Manger object with persons and vehicles")
	{
		PersonAndVehicleManager manager;
		manager.newPerson(1, "abc");
		manager.newPerson(2, "def");
		manager.newPerson(3, "ghi");
		manager.newVehicle("AA1234BB", "abc");
		manager.newVehicle("CC1234DD", "def");
		manager.newVehicle("EE1234FF", "ghi");

		WHEN("We try to create new person with alredy existing id")
		{
			THEN("Exception is thrown and no changes happend with manager")
			{
				REQUIRE_THROWS(manager.newPerson(1, "new1"));
				REQUIRE_THROWS(manager.newPerson(2, "new2"));
				REQUIRE_THROWS(manager.newPerson(3, "new3"));

				REQUIRE(manager.getAllPersons().size() == 3);
				REQUIRE(manager.getAllPersons()[0].getName() == "abc");
				REQUIRE(manager.getAllPersons()[1].getName() == "def");
				REQUIRE(manager.getAllPersons()[2].getName() == "ghi");
			}
		}
		WHEN("We try to create new vehicle with alredy existing registration number")
		{
			THEN("Exception is thrown and no changes happend with manager")
			{
				REQUIRE_THROWS(manager.newVehicle("AA1234BB", "new1"));
				REQUIRE_THROWS(manager.newVehicle("CC1234DD", "new2"));
				REQUIRE_THROWS(manager.newVehicle("EE1234FF", "new3"));

				REQUIRE(manager.getAllVehicles().size() == 3);
				REQUIRE(manager.getAllVehicles()[0].getDescription() == "abc");	
				REQUIRE(manager.getAllVehicles()[1].getDescription() == "def");
				REQUIRE(manager.getAllVehicles()[2].getDescription() == "ghi");
			}
		}

	}
}

TEST_CASE("Test relations between persons and vehicles")
{
	GIVEN("Manger object with persons and vehicles, but they aren't connected")
	{
		PersonAndVehicleManager manager;
		manager.newPerson(1, "abc");
		manager.newPerson(2, "def");
		manager.newPerson(3, "ghi");
		manager.newVehicle("AA1234BB", "abc");
		manager.newVehicle("CC1234DD", "def");
		manager.newVehicle("EE1234FF", "ghi");

		WHEN("We try to connect person and vehicle correctly")
		{
			THEN("No exceptions are thrown and everyting is set correctly")
			{
				REQUIRE_NOTHROW(manager.givePersonSingleVehicle(1, "AA1234BB"));
				REQUIRE_NOTHROW(manager.givePersonSingleVehicle(2, "CC1234DD"));
				REQUIRE_NOTHROW(manager.givePersonSingleVehicle(3, "EE1234FF"));

				REQUIRE(manager.getAllPersons()[0].getVehicles()[0]->getRegistration().getRegistrationString() == "AA1234BB");
				REQUIRE(manager.getAllVehicles()[0].getOwner()->getId() == 1);

				REQUIRE(manager.getAllPersons()[1].getVehicles()[0]->getRegistration().getRegistrationString() == "CC1234DD");
				REQUIRE(manager.getAllVehicles()[1].getOwner()->getId() == 2);

				REQUIRE(manager.getAllPersons()[2].getVehicles()[0]->getRegistration().getRegistrationString() == "EE1234FF");
				REQUIRE(manager.getAllVehicles()[2].getOwner()->getId() == 3);

			}
			
		}
		WHEN("We try to connect person and vehicle, but vehicle already has an owner")
		{
			REQUIRE_NOTHROW(manager.givePersonSingleVehicle(1, "AA1234BB"));
			THEN("New person acquires the vehicle and old one no longer has it")
			{
				REQUIRE_NOTHROW(manager.givePersonSingleVehicle(2, "AA1234BB"));

				REQUIRE(manager.getAllPersons()[0].getVehicles().size() == 0);
				REQUIRE(manager.getAllVehicles()[0].getOwner()->getId() == 2);
				REQUIRE(manager.getAllPersons()[1].getVehicles()[0]->getRegistration().getRegistrationString() == "AA1234BB");
				REQUIRE(manager.getAllVehicles()[1].getOwner() == nullptr);
				REQUIRE(manager.getAllPersons()[2].getVehicles().size() == 0);
				REQUIRE(manager.getAllVehicles()[2].getOwner() == nullptr);

				REQUIRE_NOTHROW(manager.givePersonSingleVehicle(3, "AA1234BB"));

				REQUIRE(manager.getAllPersons()[0].getVehicles().size() == 0);
				REQUIRE(manager.getAllVehicles()[0].getOwner()->getId() == 3);
				REQUIRE(manager.getAllPersons()[1].getVehicles().size() == 0);
				REQUIRE(manager.getAllVehicles()[1].getOwner() == nullptr);
				REQUIRE(manager.getAllPersons()[2].getVehicles()[0]->getRegistration().getRegistrationString() == "AA1234BB");
				REQUIRE(manager.getAllVehicles()[2].getOwner() == nullptr);

			}

		}
	}
	GIVEN("Manger object with persons and vehicles and they are connected")
	{
		PersonAndVehicleManager manager;
		manager.newPerson(1, "abc");
		manager.newPerson(2, "def");
		manager.newPerson(3, "ghi");
		manager.newVehicle("AA1234BB", "abc");
		manager.newVehicle("CC1234DD", "def");
		manager.newVehicle("EE1234FF", "ghi");
		manager.givePersonSingleVehicle(1, "AA1234BB");
		manager.givePersonSingleVehicle(2, "CC1234DD");
		manager.givePersonSingleVehicle(3, "EE1234FF");

		WHEN("Connectin is suspended")
		{
			THEN("Owner's refferencion to the vehicle is removed")
			{
				REQUIRE_NOTHROW(manager.removeVehicleFromPerson(1, "AA1234BB"));

				REQUIRE(manager.findPerson(1)->findVehicle("AA1234BB") == nullptr);
				REQUIRE(!manager.findVehicle("AA1234BB")->hasOwner());
			}
		}
		
		WHEN("Vehicle is removed")
		{
			THEN("No exceprions are thrown and also is removed owner's refferencion to the vehicle")
			{
				REQUIRE_NOTHROW(manager.deleteVehicle("AA1234BB"));

				REQUIRE(manager.findPerson(1)->findVehicle("AA1234BB") == nullptr);
				REQUIRE(manager.findVehicle("AA1234BB") == nullptr);
			}
		}
		
		WHEN("Person is removed")
		{
			THEN("No exceprions are thrown and also is removed owner's refferencion to the vehicle")
			{
				REQUIRE_NOTHROW(manager.deletePerson(1));

				REQUIRE(manager.findPerson(1) == nullptr);
				REQUIRE(!manager.findVehicle("AA1234BB")->hasOwner());
			}
		}
		
	}
}

TEST_CASE("Testing findVehicle() ")
{
	PersonAndVehicleManager manager;
	manager.newVehicle("AA1234BB", "abc");
	manager.newVehicle("CC1234DD", "def");
	manager.newVehicle("EE1234FF", "ghi");

	REQUIRE_THROWS(manager.findVehicle("abcdefg"));
	REQUIRE_THROWS(manager.findVehicle("c1234cc"));
	REQUIRE_THROWS(manager.findVehicle("BBB1234CC"));
	REQUIRE_THROWS(manager.findVehicle("BB1-234CC"));

	REQUIRE(manager.findVehicle("AA1234BB") == &manager.getAllVehicles()[0]);
	REQUIRE(manager.findVehicle("CC1234DD") == &manager.getAllVehicles()[1]);
	REQUIRE(manager.findVehicle("EE1234FF") == &manager.getAllVehicles()[2]);
}

TEST_CASE("Testing findPerson()")
{
	PersonAndVehicleManager manager;
	manager.newPerson(1, "abc");
	manager.newPerson(2, "def");
	manager.newPerson(3, "ghi");

	REQUIRE(manager.findPerson(1) == &manager.getAllPersons()[0]);
	REQUIRE(manager.findPerson(2) == &manager.getAllPersons()[1]);
	REQUIRE(manager.findPerson(3) == &manager.getAllPersons()[2]);
	REQUIRE(manager.findPerson(4) == nullptr);
	REQUIRE(manager.findPerson(5) == nullptr);
}

TEST_CASE("Testing getter methods")
{
	PersonAndVehicleManager manager;
	manager.newPerson(1, "abc");
	manager.newPerson(2, "def");
	manager.newPerson(3, "ghi");
	manager.newVehicle("AA1234BB", "abc");
	manager.newVehicle("CC1234DD", "def");
	manager.newVehicle("EE1234FF", "ghi");

	SECTION("Testing getAllPersons()")
	{
		REQUIRE(manager.getAllPersons().size() == 3);

		REQUIRE(manager.getAllPersons()[0].getId() == 1);
		REQUIRE(manager.getAllPersons()[0].getName() == "abc");

		REQUIRE(manager.getAllPersons()[1].getId() == 2);
		REQUIRE(manager.getAllPersons()[1].getName() == "def");

		REQUIRE(manager.getAllPersons()[2].getId() == 3);
		REQUIRE(manager.getAllPersons()[2].getName() == "ghi");
	}
	SECTION("Testing getAllVehicles()")
	{
		REQUIRE(manager.getAllVehicles().size() == 3);
							  
		REQUIRE(manager.getAllVehicles()[0].getRegistration().getRegistrationString() == "AA1234BB");
		REQUIRE(manager.getAllVehicles()[0].getDescription() == "abc");
							  
		REQUIRE(manager.getAllVehicles()[1].getRegistration().getRegistrationString() == "CC1234DD");
		REQUIRE(manager.getAllVehicles()[1].getDescription() == "def");
							  
		REQUIRE(manager.getAllVehicles()[2].getRegistration().getRegistrationString() == "EE1234FF");
		REQUIRE(manager.getAllVehicles()[2].getDescription() == "ghi");
	}
}
