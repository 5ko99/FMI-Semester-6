#include "catch_amalgamated.hpp"
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
#include "CommandInterpeter.h"

TEST_CASE("interpret empty str"){
    std::vector<Registration *> regs;
    std::vector<Person *> people;
    std::vector<Vehicle *> vhcls;

    CommandInterpreter ci(regs, vhcls, people);
    REQUIRE_THROWS(ci.interpret(""));
}

TEST_CASE("interpret wrong command"){
    std::vector<Registration *> regs;
    std::vector<Person *> people;
    std::vector<Vehicle *> vhcls;

    CommandInterpreter ci(regs, vhcls, people);
    REQUIRE_NOTHROW(ci.interpret("test wrong command"));
}

TEST_CASE("Remove ws"){
    std::string temp = "    test";
    CommandInterpreter::removeWs(temp);
    REQUIRE(temp == "test");
}

