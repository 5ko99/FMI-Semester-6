

#ifndef HW2_VEHICLETESTS_HPP
#define HW2_VEHICLETESTS_HPP
# include "catch.hpp"
# include "Vehicle.h"
# include <cstring>
TEST_CASE("simple initialisation", "[Vehicle]") {

    Person p("Ivan", 20);
    std::string reg = "CA6266BC";
    Registration r(reg);
    std::string descr = "Blue sedan";
    Vehicle t(r, descr);
    REQUIRE(t.getRegistration() == reg);
    REQUIRE(t.getDescription() == descr);
     t.setOwner(&p);
     REQUIRE(t.getOwner()->getName()=="Ivan");
     p.addVehicle(&t);
     REQUIRE(p.getVehicleAt(0)->getRegistration() == reg);
}

#endif //HW2_VEHICLETESTS_HPP
