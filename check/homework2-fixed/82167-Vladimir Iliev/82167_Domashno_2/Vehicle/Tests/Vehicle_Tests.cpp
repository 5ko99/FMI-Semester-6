#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Person.h"
#include "Vehicle.h"

TEST_CASE("Constructors")
{
    REQUIRE_THROWS_AS(Vehicle("Ca0000KK", "car"), std::invalid_argument);
    REQUIRE_THROWS_AS(Vehicle("CAA000KK", "car"), std::invalid_argument);
    REQUIRE_THROWS_AS(Vehicle("CA0000KKK", "car"), std::invalid_argument);
    REQUIRE_THROWS_AS(Vehicle("C0000KKK", "car"), std::invalid_argument);
    REQUIRE_NOTHROW(Vehicle("CA0000LL", "car"));
    Person vlado("Vlado", 2);
    REQUIRE_NOTHROW(Vehicle("CA0000LL", "car", vlado));
}
