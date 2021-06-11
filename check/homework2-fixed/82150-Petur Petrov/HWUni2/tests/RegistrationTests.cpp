//
// Created by pgpetrov on 4.05.21 Рі..
//

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../src/Registration.h"

TEST_CASE("Constructor") {
  REQUIRE_NOTHROW(Registration("AA1111AA"));
  REQUIRE_NOTHROW(Registration("C1234AB"));
  REQUIRE_NOTHROW(Registration("XY1111YX"));
  REQUIRE_THROWS_AS(Registration("ABC34DEF"), std::invalid_argument);
  REQUIRE_THROWS_AS(Registration("111145"), std::invalid_argument);
  REQUIRE_THROWS_AS(Registration("ABCDEF"), std::invalid_argument);
  REQUIRE_THROWS_AS(Registration("C11D"), std::invalid_argument);
}
