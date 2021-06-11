#include "../catch2/catch2.hpp"
#include "../Vehicle/Vehicle.hpp"

Registration num("HY2904YH"), num2("TG2105IF");
std::string desc = "pickup truck";
Vehicle veh(num, desc);
Vehicle veh1(num, "tractor");
Vehicle veh2(num2, "airplane");
Person per("Nj", 9 );

TEST_CASE("No owner") {
    SECTION("Number") REQUIRE(veh.getReg() == num);
    SECTION("Owner") REQUIRE(!veh.getOwner());
}

TEST_CASE("Add owner") {
    veh.setOwner(&per);
    REQUIRE(veh.getOwner() == &per);
}

TEST_CASE("Compare vehicle") {
    SECTION("Equal") REQUIRE(veh == veh1);
    SECTION("Different") REQUIRE(!(veh == veh2));
}

TEST_CASE("Remove owner") {
    veh.removeOwner();
    REQUIRE(!veh.getOwner());
}
 
