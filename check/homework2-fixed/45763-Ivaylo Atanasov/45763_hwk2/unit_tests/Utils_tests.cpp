#include "../Homework_2_2/Utils/Utils.hpp"
#include "catch2.hpp"

TEST_CASE("toUpperCase"){
    std::string t1 = "the Quick Brown fox jumped over the river 1234";
    std::string t2 = "THE QUICK BROWN FOX JUMPED OVER THE RIVER 1234";
    REQUIRE(toUpperCase(t1) == t2);
}

TEST_CASE("strToInt"){
    SECTION("correct input"){
        std::string t1 = "123456789";
        unsigned int t2 = 123456789;
        REQUIRE(strToInt(t1) == t2);
    }
    SECTION("incorrect input"){
        bool didThrow = false;
        try{
            std::string t1 = "12345m6789";
            strToInt(t1);
        } catch(const std::exception& e){
            didThrow = true;
        }
        REQUIRE(didThrow);
    }
    
}
