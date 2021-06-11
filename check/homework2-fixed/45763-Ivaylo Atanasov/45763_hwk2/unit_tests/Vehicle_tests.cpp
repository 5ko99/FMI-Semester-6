#include "../Homework_2_2/Vehicle/Vehicle.hpp"
#include "catch2.hpp"

TEST_CASE("constructor/ redefined operators"){
    SECTION("constructor"){
        Registration reg("AB1234CD");
        std::string desc = "vehi desc";
        Vehicle vehi(reg, desc);
        REQUIRE(vehi.getReg() == reg);
        REQUIRE(vehi.getDesc() == desc);
        REQUIRE(vehi.getOwnerPtr() == nullptr);
    }
    SECTION("vehicle == vehicle"){
        Registration reg1("AB1234CD");
        std::string desc1 = "vehi desc";
        Vehicle vehi1(reg1, desc1);
        
        Registration reg2("AB1234CD");
        std::string desc2 = "vehi desc";
        Vehicle vehi2(reg2, desc2);
        
        REQUIRE(vehi1 == vehi2);
    }
    SECTION("vehicle =/= vehicle"){
        Registration reg1("AB1234CD");
        std::string desc1 = "vehi desc";
        Vehicle vehi1(reg1, desc1);
        
        Registration reg2("AB4321CD");
        std::string desc2 = "vehi desc";
        Vehicle vehi2(reg2, desc2);
        
        REQUIRE(!(vehi1 == vehi2));
    }
}
