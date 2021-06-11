#include "catch_amalgamated.hpp"
#include "Registration.h"

TEST_CASE("IS NUMBER VALID TEST CASE - EMPTY STRING"){
    std::string number = "";
    REQUIRE(Registration::isNumberValid(number) == false);
}

TEST_CASE("IS NUMBER VALID TEST CASE - INVALID NUMBER"){
    std::string number = "0000000";
    REQUIRE(Registration::isNumberValid(number) == false);
}

TEST_CASE("IS NUMBER VALID TEST CASE - VALID NUMBER(8 chars)"){
    std::string number = "XY1234AV";
    REQUIRE(Registration::isNumberValid(number) == true);
}

TEST_CASE("IS NUMBER VALID TEST CASE - VALID NUMBER(7 chars)"){
    std::string number = "Y1234AV";
    REQUIRE(Registration::isNumberValid(number) == true);
}

TEST_CASE("IS NUMBER VALID TEST CASE - VALID NUMBER(more chars)"){
    std::string number = "Y1234AV1234";
    REQUIRE(Registration::isNumberValid(number) == false);
}

TEST_CASE("IS NUMBER VALID TEST CASE - VALID NUMBER(not so more chars)"){
    std::string number = "Y123V";
    REQUIRE(Registration::isNumberValid(number) == false);
}

TEST_CASE("registrationExists test case with invalid data"){
    std::string number = "asdasdsad";
    REQUIRE(Registration::registrationExists(number, nullptr) == false);
}

TEST_CASE("registrationExists test case with invalid string"){
    std::string number = "asdasd";
    std::vector<Registration*>* temp;

    REQUIRE(Registration::registrationExists(number, temp) == false);
}
