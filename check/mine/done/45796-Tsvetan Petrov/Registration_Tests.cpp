#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Registration_Header.h"

TEST_CASE("Constructor", "[Registration]")
{
	SECTION("Sucessfull") {
		Registration reg ("AS2645DD");
		Registration reg2("A3848GY");
		REQUIRE(strcmp(reg.toString(), "AS2645DD") == 0);
		REQUIRE(strcmp(reg2.toString(), "A3848GY") == 0);
	}

	SECTION("Unsucessfull") {
		bool flag = false;
		try {
			Registration reg("asd");
			flag = true;
		}
		catch (std::exception& e) {
			
		}
		REQUIRE(flag == false);

		try {
			Registration reg2("A54F");
			flag = true;
		}
		catch (std::exception& e) {

		}
		REQUIRE(flag == false);

		try {
			Registration reg3("AZ44444DH");
			flag = true;
		}
		catch (std::exception& e) {

		}
		REQUIRE(flag == false);
		
		
	}

}

TEST_CASE("Operator =") {

	SECTION("Sucessfull") {
		Registration reg("AS2645DD");
		Registration reg2("A3848GY");
		reg = "AD5558GF";
	    reg2 = "G5834FF";

		REQUIRE(strcmp(reg.toString(), "AD5558GF") == 0);
		REQUIRE(strcmp(reg2.toString(), "G5834FF") == 0);

	}

}

TEST_CASE("Operator ==") {

	SECTION("True") {
		Registration reg("AS2645DD");
		REQUIRE(reg == "AS2645DD");

		Registration reg2("A3848GY");	
		REQUIRE(reg2 == "A3848GY");
	}

	SECTION("False") {
		Registration reg("AS2645DD");
		REQUIRE(!(reg == "AS2615DD"));

		Registration reg2("A3848GY");
		REQUIRE(!(reg2 == "A3048GY"));
	}
}


