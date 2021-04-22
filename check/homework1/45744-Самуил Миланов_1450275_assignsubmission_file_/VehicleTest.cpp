#include "../Catch2/catch_amalgamated.cpp"
#include "MyString.cpp"
#include "Vehicle.cpp"
#include <cstring>

TEST_CASE("VehicleGetters"){
    Vehicle a("Poe", "The Best Car", 12);
    REQUIRE(a.space() == 12);
    REQUIRE(strcmp(a.description(), "The Best Car" ) == 0);
    REQUIRE(strcmp(a.registration(), "Poe" ) == 0);
}
