#include "../src/container.h"
#include "catch.h"

#define CATCH_CONFIG_MAIN

TEST_CASE("Container") {
    Container c{};

    const Registration r{string{"A8221YF"}};
    const string t{"text"};

    SECTION("Addition") {
        c.push(0, t);
        c.push(r, t);

        CHECK(c.contains(0));
        REQUIRE(c.contains(r));
    }

    SECTION("Relations") {
        c.push(0, t);
        c.push(r, t);

        CHECK_FALSE(c.is_dependant(0));
        CHECK_FALSE(c.is_dependant(r));

        c.acquire(0, r);

        CHECK(c.is_dependant(0));
        CHECK(c.is_dependant(r));

        c.release(0, r);

        CHECK_FALSE(c.is_dependant(0));
        REQUIRE_FALSE(c.is_dependant(r));
    }

    SECTION("Removal") {
        c.push(0, t);
        c.push(r, t);

        c.remove(0);
        c.remove(r);

        CHECK_FALSE(c.contains(0));
        REQUIRE_FALSE(c.contains(r));
    }
}
