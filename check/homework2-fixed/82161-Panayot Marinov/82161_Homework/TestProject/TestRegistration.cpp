#include "catch2.hpp"
#include "../MainProject/Headers/Registration.h"
#include <cstring>

TEST_CASE( "Registration instances can be created correctly") {
    SECTION("Registration constructor with a valid number plate") {
        Registration registration("CA1111AA");
        REQUIRE(strcmp(registration.c_str(), "CA1111AA") == 0);
    }

    SECTION("Registration constructor with another valid number plate") {
        Registration registration("C1111AA");
        REQUIRE(strcmp(registration.c_str(), "C1111AA") == 0);
    }

    SECTION("Registration constructor with an invalid number plate") {
        REQUIRE_THROWS_AS(Registration("CAA1111AA"), std::logic_error);
        CHECK_THROWS_AS(Registration("CAA1111AA"), std::logic_error);
    }

    SECTION("Registration constructor with second invalid number plate") {
        REQUIRE_THROWS_AS(Registration("C11111AA"), std::logic_error);
        CHECK_THROWS_AS(Registration("C11111AA"), std::logic_error);
    }

    SECTION("Registration constructor with third invalid number plate") {
        REQUIRE_THROWS_AS(Registration("C1111AAA"), std::logic_error);
        CHECK_THROWS_AS(Registration("C1111AAA"), std::logic_error);
    }
}

TEST_CASE("Testing Registration operator== function") {
    SECTION("Testing with a equal number plates") {
        Registration registration("CA1111AA");
        REQUIRE((registration == Registration("CA1111AA")) == true);
    }

    SECTION("Testing with another equal number plates") {
        Registration registration("C1111AA");
        REQUIRE((registration == Registration("C1111AA")) == true);
    }

    SECTION("Testing with another non-equal number plates") {
        Registration registration("CA1111AA");
        REQUIRE((registration == Registration("CA1111AB")) == false);
    }
}
