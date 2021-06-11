#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Vehicle.h"
#include "Person.h"

TEST_CASE("Add Vehicle")
{
    Person vlado("Vlado", 1);
    Person pesho("Pesho", 3);
    Vehicle v1("CA0000KK", "Cool car 1");
    Vehicle v2("C0000KK", "Cool car 2");
    Vehicle v3("PB0000KK", "Cool car 1");

    REQUIRE_NOTHROW(vlado.addVehicle(v1));
    REQUIRE_NOTHROW(vlado.addVehicle(v2));
    REQUIRE_THROWS_AS(vlado.addVehicle(v1), std::invalid_argument);
    REQUIRE_THROWS_AS(vlado.addVehicle(v2), std::invalid_argument);

    REQUIRE_NOTHROW(pesho.addVehicle(v3));
    REQUIRE_THROWS_AS(pesho.addVehicle(v3), std::invalid_argument);
    REQUIRE_THROWS_AS(vlado.addVehicle(v3), std::invalid_argument);
}

TEST_CASE("Remove Vehicle")
{
    Person vlado("Vlado", 1);
    Person pesho("Pesho", 3);
    Vehicle v1("CA0000KK", "Cool car 1");
    Vehicle v2("C0000KK", "Cool car 2");
    Vehicle v3("PB0000KK", "Cool car 1");

    vlado.addVehicle(v1);
    REQUIRE_NOTHROW(vlado.removeVehicle(v1));
    REQUIRE_THROWS_AS(vlado.removeVehicle(v1), std::invalid_argument);

    vlado.addVehicle(v1);
    vlado.addVehicle(v2);
    pesho.addVehicle(v3);

    REQUIRE_THROWS_AS(vlado.removeVehicle(v3), std::invalid_argument);
    REQUIRE_NOTHROW(vlado.removeVehicle(v1));
    REQUIRE_THROWS_AS(vlado.removeVehicle(v1), std::invalid_argument);
    REQUIRE_NOTHROW(vlado.removeVehicle(v2));
    REQUIRE_THROWS_AS(vlado.removeVehicle(v2), std::invalid_argument);

    REQUIRE_NOTHROW(pesho.removeVehicle(v3));
    REQUIRE_THROWS_AS(vlado.removeVehicle(v1), std::invalid_argument);
    REQUIRE_THROWS_AS(vlado.removeVehicle(v2), std::invalid_argument);
    REQUIRE_THROWS_AS(vlado.removeVehicle(v3), std::invalid_argument);

}
