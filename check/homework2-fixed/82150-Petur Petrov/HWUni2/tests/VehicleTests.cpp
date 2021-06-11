//
// Created by pgpetrov on 23.05.21 Рі..
//

#include "catch_amalgamated.hpp"
#include "../src/Vehicle.h"
#include "../src/Person.h"

TEST_CASE("ownership") {
  SECTION("Empty owner") {
    Vehicle vehicle(Registration("AA2222AA"), "asd asd asd");
    REQUIRE(vehicle.owner() == nullptr);
  }
  SECTION("With owner") {
    Person person("kolio", 1);
    Vehicle vehicle(Registration("AA2222AA"), "asldja", &person);
    REQUIRE(vehicle.owner() == &person);
  }
}
