#include "../Homework_2_2/Registration/Registration.hpp"
#include "catch2.hpp"

TEST_CASE("constructor/ validation check"){
    
    SECTION("correct with 8 chars"){
        bool isValid = true;
        try{
            Registration reg("AB0101CD");
        } catch(const std::exception& e){
            isValid = false;
        }
        REQUIRE(isValid);
    }
    
    SECTION("correct with 7 chars"){
        bool isValid = true;
        try{
            Registration reg("A1234ZZ");
        } catch(const std::exception& e){
            isValid = false;
        }
        REQUIRE(isValid);
    }
    
    SECTION("wrong, ends with only 1 letter"){
        bool isValid = true;
        try{
            Registration reg("AB2222C");
        } catch(const std::exception& e){
            isValid = false;
        }
        REQUIRE(isValid == false);
    }

    // proverka za gengsta nomer
    SECTION("wrong, ends with no letters"){
        bool isValid = true;
        try{
            Registration reg("AB777777");
        } catch(const std::exception& e){
            isValid = false;
        }
        REQUIRE(isValid == false);
    }
    
    SECTION("wrong, starts with 1 letter ends with 3"){
        bool isValid = true;
        try{
            Registration reg("A1234CDF");
        } catch(const std::exception& e){
            isValid = false;
        }
        REQUIRE(isValid == false);
    }
    
    SECTION("wrong, too few numbers"){
        bool isValid = true;
        try{
            Registration reg("AB000CD");
        } catch(const std::exception& e){
            isValid = false;
        }
        REQUIRE(isValid == false);
    }
    
    SECTION("wrong, too many numbers"){
        bool isValid = true;
        try{
            Registration reg("AB123456CD");
        } catch(const std::exception& e){
            isValid = false;
        }
        REQUIRE(isValid == false);
    }
}

TEST_CASE("redefined operators"){
    
    SECTION("reg == reg"){
        Registration reg1("AB1234CD");
        Registration reg2("AB1234CD");
        REQUIRE(reg1 == reg2);
    }
    SECTION("reg =/= reg"){
        Registration reg1("AB1234CD");
        Registration reg2("AB4321CD");
        REQUIRE(!(reg1 == reg2));
    }
    
    SECTION("reg == char*"){
        Registration reg1("AB1234CD");
        char regstr[] = "AB1234CD";
        REQUIRE(reg1 == regstr);
    }
    SECTION("reg =/= char*"){
        Registration reg1("AB1234CD");
        char regstr[] = "AB4321CD";
        REQUIRE(!(reg1 == regstr));
    }
    
    SECTION("reg == std::string"){
        Registration reg1("AB1234CD");
        std::string regstr = "AB1234CD";
        REQUIRE(reg1 == regstr);
    }
    SECTION("reg =/= std::string"){
        Registration reg1("AB1234CD");
        std::string regstr = "AB4321CD";
        REQUIRE(!(reg1 == regstr));
    }
    
    
    SECTION("reg = char*"){
        char chp[] = "AB1010BA";
        Registration reg = chp;
        REQUIRE(reg == chp);
    }
    SECTION("reg = reg"){
        Registration reg1("AB1111CD");
        Registration reg2 = reg1;
        REQUIRE(reg1 == reg2);
    }
}

TEST_CASE("other functions"){
    SECTION("toCharArr"){
        Registration reg("AB1234CD");
        bool isSame = !strcmp(reg.toCharArr(), "AB1234CD");
        REQUIRE(isSame);
    }
}
    
