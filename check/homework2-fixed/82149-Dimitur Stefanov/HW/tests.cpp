//
// Created by pgpetrov on 23.05.21 Рі..
//

#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"
#include "DataManager.h"

TEST_CASE("Registration")
{
	REQUIRE_NOTHROW(Registration("DD9897SS"));
	REQUIRE_THROWS(Registration("DD987897DD"));
	REQUIRE_THROWS(Registration("dd908098"));
	REQUIRE_THROWS(Registration(""));
}

TEST_CASE("Vehicle")
{
	Vehicle myVehicle(Registration("KJ9876HG"), "asdc kjshd");
	REQUIRE(myVehicle.getRegistration() == Registration("KJ9876HG"));
	Person owner("gosho", 1);
	myVehicle.setOwner(&owner);
	REQUIRE(myVehicle.getOwner() == &owner);
}

TEST_CASE("Person")
{
	Vehicle myVehicle(Registration("KJ9876HG"), "asdc kjshd");
	Vehicle myVehicle1(Registration("KJ9876HG"), "asdc kjshd");
	Person gosho("gosho", 1);
	REQUIRE_NOTHROW(gosho.addVehicle(&myVehicle));
	REQUIRE_THROWS(gosho.addVehicle(&myVehicle1));
	REQUIRE_NOTHROW(gosho.removeVehicle(myVehicle.getRegistration()));
	REQUIRE_THROWS(gosho.removeVehicle(Registration("AS9876AS")));
}

TEST_CASE("DataManager")
{
	DataManager d;
	REQUIRE_NOTHROW(d.addVehicle(Registration("KJ9876HG"), "asdc kjshd"));
	REQUIRE_NOTHROW(d.addVehicle(Registration("AS1233AA"), "a"));
	REQUIRE_NOTHROW(d.addVehicle(Registration("BB2897SS"), "b"));
	REQUIRE_NOTHROW(d.addVehicle(Registration("CC8626LL"), "c"));

	REQUIRE_NOTHROW(d.addPerson("gosho", 1));
	REQUIRE_NOTHROW(d.addPerson("pesho", 2));
	REQUIRE_NOTHROW(d.addPerson("georgi", 3));

	REQUIRE_THROWS(d.addPerson("gosho-kopie", 1));
	REQUIRE_THROWS(d.addVehicle(Registration("CC8626LL"), "d"));

	REQUIRE_NOTHROW(d.acquire(1, Registration("CC8626LL")));
	REQUIRE_NOTHROW(d.acquire(2, Registration("CC8626LL")));
	REQUIRE_NOTHROW(d.acquire(3, Registration("BB2897SS")));
}
