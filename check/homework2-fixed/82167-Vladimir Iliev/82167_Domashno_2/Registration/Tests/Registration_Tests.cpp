#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Registration.h"

TEST_CASE("Registration constructor")
{
    REQUIRE_NOTHROW(Registration("CA0000RV"));
    REQUIRE_NOTHROW(Registration("C0000RV"));
    REQUIRE_THROWS_AS(Registration("C00000RV"), std::invalid_argument);
    REQUIRE_THROWS_AS(Registration("c0000rv"), std::invalid_argument);
    REQUIRE_THROWS_AS(Registration("120000RV"), std::invalid_argument);
    REQUIRE_THROWS_AS(Registration("AAAAAAAA"), std::invalid_argument);
    REQUIRE_THROWS_AS(Registration("12000011"), std::invalid_argument);
    REQUIRE_THROWS_AS(Registration("AA0000"), std::invalid_argument);
}
