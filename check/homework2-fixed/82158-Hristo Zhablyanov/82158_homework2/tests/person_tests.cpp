#include "../src/person.h"
#include "catch.h"

#define CATCH_CONFIG_MAIN

using std::invalid_argument;

TEST_CASE("Person") {
    SECTION("Constructor & Getter") {
        Person p(0, string{"name"});
        CHECK(p.get_id() == 0);
        REQUIRE_FALSE(p.has_vehicles());
    }

    Person p1(0, string{"A"});
    Person p2(1, string{"B"});
    Vehicle v1(Registration{string{"Z9284CO"}}, string{"A"});
    Vehicle v2(Registration{string{"XY1111YX"}}, string{"B"});

    SECTION("Acquire") {
        CHECK_NOTHROW(p1.acquire(&v1));

        CHECK(p1.has_vehicles());
        CHECK(v1.has_owner());
        CHECK(v1.get_owner() == &p1);

        CHECK_THROWS_AS(p2.acquire(&v1), invalid_argument);
        CHECK_FALSE(p2.has_vehicles());
        CHECK(v1.has_owner());
        REQUIRE(v1.get_owner() == &p1);
    }

    SECTION("Release") {
        p1.acquire(&v1);
        p1.release(v1.get_registration());

        CHECK_FALSE(p1.has_vehicles());
        REQUIRE_FALSE(v1.has_owner());
    }

    SECTION("Acquire After Release") {
        p1.acquire(&v1);
        p1.release(v1.get_registration());

        CHECK_NOTHROW(p2.acquire(&v1));
        CHECK_NOTHROW(p2.acquire(&v2));

        CHECK(p2.has_vehicles());

        CHECK(v1.has_owner());
        CHECK(v1.get_owner() == &p2);

        CHECK(v2.has_owner());
        REQUIRE(v2.get_owner() == &p2);
    }

    SECTION("Clear") {
        p2.acquire(&v1);
        p2.acquire(&v2);

        p2.clear();

        CHECK_FALSE(p2.has_vehicles());

        CHECK_FALSE(v1.has_owner());
        REQUIRE_FALSE(v2.has_owner());
    }
}
