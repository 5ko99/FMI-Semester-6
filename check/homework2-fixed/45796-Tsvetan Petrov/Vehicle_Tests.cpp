#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Vehicle_Header.h"

TEST_CASE("Constructor", "[Registration]")
{
	SECTION("Sucessfull") {
		Vehicle car1("GH4964JK", "description of the first car !849#");
		REQUIRE(car1.descr() == "description of the first car !849#");
		REQUIRE(car1.registration() == "GH4964JK");

		Vehicle car2("H4964JK", "description of the second car !849#");
		REQUIRE(car2.descr() == "description of the second car !849#");
		REQUIRE(car2.registration() == "H4964JK");
	}
}

TEST_CASE("Set\get owner") {
	Vehicle car1("GH4964JK", "description of the first car !849#");
	car1.set_owner("Ivan");
	REQUIRE(car1.get_owner() == "Ivan");

	Vehicle car2("H4960JK", "description of the second car !849#");
	car2.set_owner("4335");
	REQUIRE(car2.get_owner() == "");
}

TEST_CASE("Operator ==") {

	SECTION("True") {
		Vehicle car1("GH4964JK", "description of the first car !849#");
		Vehicle car2("GH4964JK", "description of the second car !849#");
		bool check = (car1 == car2);
		REQUIRE(check);
	}

	SECTION("False") {
		Vehicle car3("GH4964JK", "description of the first car !849#");
		Vehicle car4("H4960JK", "description of the second car !849#");
		bool check2 = (car3 == car4);
		REQUIRE(!check2);
	}
}

TEST_CASE("Set owner ID") {

	SECTION("Sucessfull") {
		Vehicle car1("GH4964JK", "description of the first car !849#");
		Vehicle car2("GH4964JK", "description of the second car !849#");
		car1.set_owner_id(65);
		car2.set_owner_id(2678593);
		REQUIRE(car1.get_owner_id() == 65);
		REQUIRE(car2.get_owner_id() == 2678593);
	}

	
}
