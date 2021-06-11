//
// Created by pgpetrov on 23.05.21 Рі..
//

#include "catch_amalgamated.hpp"
#include "../src/Vehicle.h"
#include "../src/Person.h"

TEST_CASE("ownership of vehicles") {
  Vehicle v1(Registration("AA1111AA"), "asldkja sldkj asd");
  Vehicle v2(Registration("BB2222BB"), "asldkja sldkj asd");
  Person p("myname", 1);
  REQUIRE(p.owned_vehicles().empty());
  REQUIRE_NOTHROW(p.acquire_vehicle(v1));
  REQUIRE(p.owned_vehicles().size() == 1);
  REQUIRE_THROWS_AS(p.acquire_vehicle(v1), std::logic_error);
  REQUIRE_NOTHROW(p.acquire_vehicle(v2));
  REQUIRE(p.owned_vehicles().size() == 2);
  REQUIRE_NOTHROW(p.disown_vehicle(v1.registration()));
  REQUIRE_NOTHROW(p.acquire_vehicle(v1));
  REQUIRE(p.owned_vehicles().size() == 2);
  REQUIRE_THROWS_AS(p.acquire_vehicle(v1), std::logic_error);
}
