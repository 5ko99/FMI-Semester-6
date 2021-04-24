#define CATCH_CONFIG_MAIN
#include <cstring>
#include "catch2.hpp"
#include "myString.h"
#include "vehicle.h"

TEST_CASE ("accessors") {

    Vehicle test("A 1234 AA", "A sport car.", 1);

    CHECK(!strcmp(test.getRegistration(), "A 1234 AA"));
    CHECK(!strcmp(test.getDescription(), "A sport car."));
    CHECK(test.getSpace() == 1);
    
}