#include "catch2.hpp"
#include<cassert>
#include "Vehicle.h"
#include "Person.h"

TEST_CASE("Vehicle constructor", "[Vehicle]") {
	SECTION("constructor_givenValidArguments_InitializeObjProperly") {
		//Arrange
		Vehicle v("X1234BB", "Audi A3");

		//Act
		bool areEqualReg = v.getRegistration() == "X1234BB";

		//Assert
		REQUIRE(areEqualReg == true);
		REQUIRE(v.getOwnerID() == 0);
	}
}

TEST_CASE("Vehicle getRegistration", "[getRegistration]") {
	SECTION("getRegistration_ReturnProperString") {
		//Arrange
		Vehicle v("X1234BB", "Audi A3");

		//Act
		bool areEqualReg = v.getRegistration() == "X1234BB";

		//Assert
		REQUIRE(areEqualReg == true);
	}
}

TEST_CASE("Vehicle setOwner", "[setOwner]") {
	SECTION("setOwner_ValidOwnerId_SetItProperly") {
		//Arrange
		Vehicle v("X1234BB", "Audi A3");
		Person p("Petko", 100);

		//Act
		v.setOwnerId(p.getID());

		//Assert
		REQUIRE(v.getOwnerID() == p.getID());
	}
}

TEST_CASE("Vehicle getOwnerId", "[getOwnerId]") {
	SECTION("getOwnerId_returnIdProperly") {
		//Arrange
		Vehicle v("X1234BB", "Audi A3");
		Person p("Petko", 100);

		//Act
		v.setOwnerId(p.getID());
		bool areEqual = v.getOwnerID() == p.getID();

		//Assert
		REQUIRE(areEqual == true);
	}
}
