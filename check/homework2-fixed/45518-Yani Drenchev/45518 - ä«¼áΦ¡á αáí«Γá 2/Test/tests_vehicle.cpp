//
// Created by Yani Drenchev on 18.05.21.
//

#include "../Source/Vehicle.cpp"
#include "single_include/catch2/catch.hpp"


TEST_CASE("vehicle get registration valid tests", "[person id valid]") {
   Registration registration("ST1234ST");
   Vehicle veh1("ST1234ST", "desc");
   Vehicle veh2("ST1234SS", "desc");
   REQUIRE(veh1.getRegistration() == registration);
   bool check = veh2.getRegistration() == registration;
   REQUIRE(!check);
}

TEST_CASE("vehicle get person valid tests", "[vehicle person valid]") {
    Registration registration("ST1234ST");
    Vehicle veh1("ST1234ST", "desc");
    REQUIRE(veh1.getPerson() == 0);
    veh1.setPerson(1);
    REQUIRE(veh1.getPerson() == 1);
}

TEST_CASE("vehicle operator == ", "[vehicle operator ==]") {
    Vehicle veh1("ST1234ST", "desc");
    Vehicle veh2("ST1234ST", "desc");
    Vehicle veh3("ST1234TT", "desc");
    bool check = veh1 == veh3;
    REQUIRE(!check);
}
