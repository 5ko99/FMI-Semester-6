#include "../src/vehicle.h"
#include "catch.h"

#define CATCH_CONFIG_MAIN

TEST_CASE("Vehicle") {
    SECTION("Constructor & Getters") {
        const char* s = "AB0123CD";
        Registration r(s);
        Vehicle v(r, string{"car"});
        CHECK(v.get_registration() == s);
        CHECK(v.get_owner() == nullptr);
        REQUIRE_FALSE(v.has_owner());
    }
}
