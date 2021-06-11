#define CATCH_CONFIG_MAIN
#include "Registration.h"
#include<cassert>
#include "catch2.hpp"

TEST_CASE("Registration constructor", "[Registration]") {
	SECTION("Registration_GivenValidCarRegNumber_InitializeRegistrationProperly") {
		//Arrange
		char reg[] = "XX1234YY";
		Registration s(reg);
		bool areEqual = true;
		size_t i;

		//Act
		for (i = 0; i < 9; i++)
		{
			if (s.toString()[i] != reg[i])
			{
				areEqual = false;
				break;
			}
		}

		//Assert
		REQUIRE(areEqual == true);
	}

	SECTION("Registration_GivenInvalidCarRegNumber_Throws") {
		//Arrange
		char reg1[] = "X234YY";
		char reg2[] = "X1234Y";

		//Assert
		REQUIRE_THROWS(Registration(reg1));
		REQUIRE_THROWS(Registration(reg2));
	}
}

TEST_CASE("Registration operator=", "[operator=]") {
	SECTION("operator=_givenTheSameObject_DoesNothing") {
		//Arrange
		char reg[] = "XX1234YY";
		Registration s(reg);

		//Act
		s = s;

		//Assert
		REQUIRE(s.toString() == reg);
	}

	SECTION("operator=_GivenCorrectRegistrationObject_CopyProperly") {
		//Arrange
		char reg[] = "XX1234YY";
		Registration s(reg);
		Registration k("AB4321VG");

		//Act
		s = k;
		bool areEqual = s == k;

		//Assert
		REQUIRE(areEqual == true);
	}

	SECTION("operator=_GivenTwoConsecutiveObjects_CopyProperly") {
		//Arrange
		char reg[] = "XX1234YY";
		Registration s(reg);
		Registration k("AB4321VG");
		Registration b("OK4321AB");

		//Act
		s = k = b;
		bool areEqual = s == b;

		//Assert
		REQUIRE(areEqual == true);
	}
}

TEST_CASE("Registration operator==", "[operator==]") {
	SECTION("operator==_givenDifferentStrings_False") {
		//Arrange
		Registration s("A1234BB");
		Registration t("B1234AA");

		//Act
		bool areEqual = s == t;

		//Assert
		REQUIRE(areEqual == false);
	}

	SECTION("operator==_givenEqualStrings_True") {
		//Arrange
		Registration s("A1234BB");
		Registration t("A1234BB");

		//Act
		bool areEqual = s == t;

		//Assert
		REQUIRE(areEqual == true);
	}
}

TEST_CASE("Registration toString", "[toString]") {
	SECTION("toString()_ShouldReturnRefToString") {
		//Arrange
		Registration s("A1234BB");

		//Act
		string cpy = s.toString();

		//Assert
		REQUIRE(cpy == s.toString());
	}
}
