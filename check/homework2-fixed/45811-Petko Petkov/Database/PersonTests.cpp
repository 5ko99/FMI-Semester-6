#include "catch2.hpp"
#include<cassert>
#include "Person.h"
#include "Registration.h"

TEST_CASE("Person constructor", "[Person]") {
	SECTION("constructor_givenValidArguments_InitializeObjProperly") {
		//Arrange
		Person p("Petko", 10);

		//Act
		bool areEqual = p.getID() == 10;

		//Assert
		REQUIRE(areEqual == true);
	}
}

TEST_CASE("Person getId", "[getId]") {
	SECTION("getId_returnIdProperly") {
		//Arrange
		Person p("Petko", 10);

		//Assert
		REQUIRE(p.getID() == 10);
	}
}

TEST_CASE("Person getRegistrationsCount", "[getRegistrationsCount]") {
	SECTION("getRegistrationsCount_WithNonEmptyList_ReturnSizeGreaterThanZero") {
		//Arrange
		Person p("Petko", 10);

		//Act
		p.addRegistrationNumber("X1234BB");

		//Assert
		REQUIRE(p.getRegistrationsCount() > 0);
	}

	SECTION("getRegistrationsCount_WithOneElement_ReturnOne") {
		//Arrange
		Person p("Petko", 10);

		//Act
		p.addRegistrationNumber("X1234BB");

		//Assert
		REQUIRE(p.getRegistrationsCount() == 1);
	}

	SECTION("getRegistrationsCount_OnEmptyList_ReturnZero") {
		//Arrange
		Person p("Petko", 10);

		//Assert
		REQUIRE(p.getRegistrationsCount() == 0);
	}
}

TEST_CASE("Person getIndexOf", "[getIndexOf]") {
	SECTION("getIndexOf_ExistingRegistration_ReturnItProperly") {
		//Arrange
		Person p("Petko", 10);
		Registration r("X1234BB");

		//Act
		p.addRegistrationNumber(r.toString());

		//Assert
		REQUIRE(p.getIndexOf(r.toString()) == 0);
	}

	SECTION("getIndexOf_NonExistingRegistration_ReturnMinusOne") {
		//Arrange
		Person p("Petko", 10);

		//Act
		size_t ind = p.getIndexOf("X1234BB");

		//Assert
		REQUIRE(ind == -1);
	}
}

TEST_CASE("Person removeRegistrationNumber", "[removeRegistrationNumber]") {
	SECTION("removeRegistrationNumber_GivenExistingRegistration_RemoveItAccordingly") {
		//Arrange
		Person p("Petko", 10);
		Registration r("X1234BB");

		//Act
		p.addRegistrationNumber(r.toString());
		p.removeRegistrationNumber(r.toString());

		//Assert
		REQUIRE(p.getRegistrationsCount() == 0);
	}

	SECTION("removeRegistrationNumber_GivenNonExistingRegnum_Throw") {
		//Arrange
		Person p("Petko", 10);

		//Assert
		REQUIRE_THROWS(p.removeRegistrationNumber("X1234BB"));
		REQUIRE_THROWS_AS(p.removeRegistrationNumber("X1234BB"), std::invalid_argument);
	}
}

TEST_CASE("Person addRegistrationNumber", "[addRegistrationNumber]") {
	SECTION("addRegistrationNumber_GivenProperRegistration_AddItAccordingly") {
		//Arrange
		Person p("Petko", 10);
		Registration r("X1234BB");

		//Act
		p.addRegistrationNumber(r.toString());

		//Assert
		REQUIRE(p.getRegistrationsCount() == 1);
	}

	SECTION("addRegistrationNumber_GivenDuplicateRegistration_Throw") {
		//Arrange
		Person p("Petko", 10);
		Registration r("X1234BB");

		//Act
		p.addRegistrationNumber(r.toString());

		//Assert
		REQUIRE_THROWS(p.addRegistrationNumber(r.toString()));
		REQUIRE_THROWS_AS(p.addRegistrationNumber(r.toString()), std::invalid_argument);
	}
}

TEST_CASE("Person getRegistrationAt", "[getRegistrationAt]") {
	SECTION("getRegistrationAt_OnNonEmptyList_ReturnRegistrationProperly") {
		//Arrange
		Person p("Petko", 10);
		Registration r("X1234BB");

		//Act
		p.addRegistrationNumber(r.toString());

		//Assert
		REQUIRE(p.getRegistrationAt(0) == r.toString());
	}

	SECTION("getRegistrationAt_AtInvalidIndex_Throw") {
		//Arrange
		Person p("Petko", 10);
		Registration r("X1234BB");

		//Act
		p.addRegistrationNumber(r.toString());

		//Assert
		REQUIRE_THROWS(p.getRegistrationAt(10));
		REQUIRE_THROWS_AS(p.getRegistrationAt(10), std::out_of_range);
	}
}
