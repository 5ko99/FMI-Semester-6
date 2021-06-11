#include <stdexcept>

#include "../src/registration.h"
#include "catch.h"

#define CATCH_CONFIG_MAIN

using std::invalid_argument;

TEST_CASE("Registration") {
    SECTION("Constructor") {
        CHECK_NOTHROW(Registration("C1234Ab"));
        CHECK_NOTHROW(Registration("xY1111yX"));

        CHECK_THROWS_AS(Registration("C11D"), invalid_argument);
        CHECK_THROWS_AS(Registration("111145"), invalid_argument);
        CHECK_THROWS_AS(Registration("ABCDEF"), invalid_argument);
        REQUIRE_THROWS_AS(Registration("ABC34DEF"), invalid_argument);
    }

    const char* s = "UI0123AZ";

    SECTION("Getter") {
        Registration r(s);
        REQUIRE(!std::strcmp(r.str(), s));
    }

    SECTION("Operator ==") {
        Registration r1(s);
        Registration r2(r1);
        Registration r3("UI9123AZ");
        CHECK(r1 == r2);
        CHECK(r1 == s);
        CHECK(r2 == s);
    }
}
