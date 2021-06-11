#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Person_header.h"

TEST_CASE("Constructor") {

	Person pers("Rei Kawakubo", 3);
	REQUIRE(pers.get_name() == "Rei Kawakubo");
	REQUIRE(pers.get_id() == 3);
	REQUIRE(pers.number_of_cars() == 0);

}

TEST_CASE("Assign vehicle") {

	Person pers("Rei Kawakubo", 3);
	Vehicle* veh = new(std::nothrow) Vehicle("KJ8246NB", "descr");
	pers.assign_vehicle(veh);
	REQUIRE(pers.number_of_cars() == 1);

}

TEST_CASE("Remove vehicle") {

	Person pers("Rei Kawakubo", 3);
	Vehicle* veh = new(std::nothrow) Vehicle("KJ8246NB", "descr");
	if (veh != nullptr) {
		pers.assign_vehicle(veh);
		pers.remove_vehicle(veh);
		REQUIRE(pers.number_of_cars() == 0);
	}
	
}

TEST_CASE("Number of cars") {
	Person pers("Rei Kawakubo", 3);
	Vehicle* veh = new(std::nothrow) Vehicle("KJ8246NB", "descr");
	if (veh != nullptr) {
		pers.assign_vehicle(veh);
		REQUIRE(pers.number_of_cars() == 1);
		Vehicle* veh2 = new(std::nothrow) Vehicle("KJ8246NB", "descr");
		if (veh2 != nullptr) {
			pers.assign_vehicle(veh2);
			REQUIRE(pers.number_of_cars() == 2);
			Vehicle* veh3 = new(std::nothrow) Vehicle("KJ8246NB", "descr");
			if (veh3 != nullptr) {
				pers.assign_vehicle(veh3);
				REQUIRE(pers.number_of_cars() == 3);
			}
		}
	}
}

TEST_CASE("Operator ==") {
	Person pers("Rei Kawakubo", 3);
	Person pers2("Rei Kawakubo", 3);
	Person pers3("Martin Margiela", 14);

	REQUIRE((pers == pers2));
	REQUIRE(!(pers == pers3));
}
